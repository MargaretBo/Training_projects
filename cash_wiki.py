import sys
import argparse
from bs4 import BeautifulSoup 
import logging
import json
import requests
import typing

logging.basicConfig(
level=logging.INFO, 
format='%(asctime)s - %(levelname)s - %(message)s'
)
handler = logging.StreamHandler(sys.stdout)


class WikiGraph:
    """
    Class WikiGraph is a class that creates a graph of Wikipedia pages and saves it to a JSON file.
    """
    def __init__(self): 
        self.depth_ = 3
        self.starting_page_name_ = 'Erzya language'
        self.starting_page_url_ = 'https://en.wikipedia.org/wiki/Erzya_language'
        self.nodes_number_ = 0

    def parse_arguments(self):
        """Parces the staring page name and the desired depth of the graph from the command line."""
        parser = argparse.ArgumentParser(description='Parcing the name and depth from the command line')
        parser.add_argument('-p', '--page', type = str, help = 'Specify the name of the page')
        parser.add_argument('-d', '--depth', type = int, help = 'Specify the depth')
        args = parser.parse_args()
        if args.page is not None:
            self.starting_page_name_ = args.page 
        if args.depth is not None:
            self.depth_ = args.depth
        if self.depth_ < 1:
            print('Depth must be greater than 0')
            sys.exit(1)
        self.starting_page_url_ = 'https://en.wikipedia.org/wiki/'+ self.starting_page_name_.replace(' ', '_')

    def soup_wrapper(self, content: str, page_name: str, page_url: str) -> typing.List[typing.Any]:
        """
        Filters the links to leave only internal wikipedia links from the page.
        Wraps the content of the page in a BeautifulSoup object. Much faster than any Wikipedia api that I could find.
        """
        soup = BeautifulSoup(content, 'html.parser')
        part_url = '/wiki/' + page_name.replace(' ', '_')
        base_request = requests.get(page_url)
        soup = BeautifulSoup(base_request.content, 'html.parser')
        links = soup.find_all('a', href=True)
        seen_hrefs = set()
        filtered_links = []
        for link in links:
            href = link['href']
            if (href.startswith('/wiki/') and
                ':' not in href and
                href != '/wiki/Main_Page' and
                href != part_url and
                href not in seen_hrefs):
                seen_hrefs.add(href)
                filtered_links.append(link)
        return filtered_links

    def get_links(self, graph, page_list, page_url, page_name = None,  current_depth = 0):
        """
        Recursively gets the links from the page and adds them to the graph
        """
        current_depth += 1
        base_request = requests.get(page_url)
        if base_request.status_code == 200:
            if self.nodes_number_ == 0:
                self.nodes_number_ += 1
                graph['nodes'].append({'name': page_name, 'link': page_url})
                logging.info(f'Visiting page: {page_name} - {page_url}')
                page_list.append(page_url)
            links = self.soup_wrapper(base_request.content, page_name, page_url)
            links_to_visit = []
            for link in links:
                ending_page_url = 'https://en.wikipedia.org' + link.get('href')
                ending_page_title = link.get('href').replace('/wiki/', '').replace('_', ' ')
                if self.nodes_number_ > 1000:
                    break
                logging.info(f'Visiting page: {ending_page_title} - {ending_page_url}')
                if ending_page_url not in page_list:
                    graph['nodes'].append({'name': ending_page_title, 'link': ending_page_url})
                    self.nodes_number_ += 1
                    links_to_visit.append((ending_page_url, ending_page_title))
                    page_list.append(ending_page_url)
                graph['edges'].append({'source': page_name, 'target': ending_page_title, 'link': ending_page_url})
            for ending_page_url, ending_page_title in links_to_visit:
                if self.nodes_number_ > 1000:
                    break
                if  current_depth < self.depth_:
                    self.get_links(graph, page_list, ending_page_url, ending_page_title, current_depth)
        else:
            print('Page does not exist')
            sys.exit(1)

    def make_graph(self):
        graph = {
            'nodes': [],
            'edges': []
        }
        page_list = []
        self.get_links(graph, page_list, self.starting_page_url_, self.starting_page_name_, 0)
        with open('wiki.json', 'w') as f:
            json.dump(graph, f, indent = 4)


wikigraph = WikiGraph()
wikigraph.parse_arguments()
wikigraph.make_graph()
print(f'Nodes: {wikigraph.nodes_number_}')
