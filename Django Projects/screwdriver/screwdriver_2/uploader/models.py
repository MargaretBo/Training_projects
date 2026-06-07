from django.db import models
from django.core.exceptions import ValidationError
from django.utils.translation import gettext_lazy as _

def validate_audio_file(value):
    allowed_extensions = ['mp3', 'ogg', 'wav']
    extension = value.name.split('.')[-1].lower()
    if extension not in allowed_extensions:
        raise ValidationError(
            _('Non-audio file detected'),
            code='non_audio_file',  # Use a unique code to avoid conflicts
        )

class Upload(models.Model):
    upload_file = models.FileField(validators=[validate_audio_file])
    upload_date = models.DateTimeField(auto_now_add=True)

def __str__(self):
        return self.file_path
