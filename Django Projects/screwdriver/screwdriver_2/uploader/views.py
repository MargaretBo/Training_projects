from django.shortcuts import render
from django.views.generic.edit import CreateView
from django.urls import reverse_lazy
from .models import Upload
from django.views.decorators.csrf import csrf_exempt
from django.utils.decorators import method_decorator
import os
from django.conf import settings    
from django.http import JsonResponse

# @csrf_exempt
@method_decorator(csrf_exempt, name='dispatch')
class UploadView(CreateView):
    model = Upload
    fields = ['upload_file', ]
    success_url = reverse_lazy('fileupload')
    def get_context_data(self, **kwargs):
        context = super().get_context_data(**kwargs)
        context['documents'] = Upload.objects.all()
        return context

    def post(self, request, *args, **kwargs):
        if 'file' in request.FILES:
            uploaded_file = request.FILES['file']
            file_path = os.path.join(settings.MEDIA_ROOT, uploaded_file.name)
            with open(file_path, 'wb+') as destination:
                for chunk in uploaded_file.chunks():
                    destination.write(chunk)
            Upload.objects.create(upload_file=uploaded_file)
            return JsonResponse({'message': 'File uploaded successfully'})
        else:
            return super().post(request, *args, **kwargs)