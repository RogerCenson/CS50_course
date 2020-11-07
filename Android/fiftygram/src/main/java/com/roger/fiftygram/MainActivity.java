package com.roger.fiftygram;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.os.ParcelFileDescriptor;
import android.provider.MediaStore;
import android.util.Log;
import android.view.View;
import android.widget.ImageView;

import com.bumptech.glide.Glide;
import com.bumptech.glide.load.Transformation;
import com.bumptech.glide.request.RequestOptions;

import java.io.FileDescriptor;
import java.io.FileNotFoundException;
import java.io.IOException;

import jp.wasabeef.glide.transformations.BlurTransformation;
import jp.wasabeef.glide.transformations.gpu.PixelationFilterTransformation;
import jp.wasabeef.glide.transformations.gpu.SepiaFilterTransformation;
import jp.wasabeef.glide.transformations.gpu.SketchFilterTransformation;
import jp.wasabeef.glide.transformations.gpu.ToonFilterTransformation;

public class MainActivity extends AppCompatActivity implements ActivityCompat.OnRequestPermissionsResultCallback {
    private ImageView imageView;
    private Bitmap image;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        imageView = findViewById(R.id.image_view);

        requestPermissions(new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, 1);
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

    public void choosePhoto(View v) {
        Intent intent = new Intent(Intent.ACTION_OPEN_DOCUMENT);
        intent.setType("image/*");
        startActivityForResult(intent, 1);
    }

    public void apply(Transformation<Bitmap> filter) {
        Glide.
                with(this)
                .load(image)
                .apply(RequestOptions.bitmapTransform(filter))
                .into(imageView);
    }
    public void applySepia(View v) {
        apply(new SepiaFilterTransformation());
    }

    public void applyBlur(View v) {
        apply(new BlurTransformation());
    }

    public void applySketch(View v) {
        apply(new SketchFilterTransformation());
    }

    public void saveImage(View v) {
        //get image as bitmap from view
        if(imageView.getDrawable() == null){
            return;
        }
        Log.d("save photo", String.valueOf(System.currentTimeMillis()));
        BitmapDrawable bitmapDrawable = (BitmapDrawable) imageView.getDrawable();
        MediaStore.Images.Media.insertImage(getContentResolver(), bitmapDrawable.getBitmap(),
                "Fiftygram_"+String.valueOf(System.currentTimeMillis()),"");
    }
    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
         super.onActivityResult(requestCode, resultCode, data);

         if (resultCode == Activity.RESULT_OK && data != null) {
             try {
                 Uri uri = data.getData();
                 ParcelFileDescriptor parcelFileDescriptor =
                         getContentResolver().openFileDescriptor(uri, "r");
                 FileDescriptor fileDescriptor = parcelFileDescriptor.getFileDescriptor();
                 image = BitmapFactory.decodeFileDescriptor(fileDescriptor);
                 parcelFileDescriptor.close();
                 imageView.setImageBitmap(image);
             }
             catch (IOException e) {
                 Log.e("cs50","Image not found", e);
             }
         }
    }
}