import os
import subprocess
import sys
import shutil
import requests
from audio_type_check import is_audio

def show_list():
    if sys.argv[1] == 'list':
        items = os.listdir('screwdriver_2/media')
        for item in items:
            print(item)

def upload_file():
    if  sys.argv[1] == 'upload':
        file_path = sys.argv[2]
        try:
            if not is_audio(file_path):
                print("Non-audio file detected")
                return
            files = {'file': open(file_path, 'rb')}
            response = requests.post('http://localhost:8888/', files=files)
            if response.status_code == 200:
                print(f"File {file_path} uploaded successfully")
            else:
                print(f"File {file_path} not uploaded")
        except Exception as e:
            print(f"An error occurred: {e}")

def run_django_server(project_path):
    try:
        os.chdir(project_path)
        subprocess.run([sys.executable, 'manage.py', 'runserver'], check=True)
    except subprocess.CalledProcessError as e:
        print(f"Error running Django server: {e}")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == '__main__':
    project_path = 'screwdriver_2'
    print(len(sys.argv))
    if len(sys.argv) >= 2:
        show_list()
        upload_file()
    else:
        run_django_server(project_path)