package com.android.espcontrol;

import static androidx.constraintlayout.helper.widget.MotionEffect.TAG;

import androidx.appcompat.app.AppCompatActivity;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.util.Log;
import android.view.MotionEvent;
import android.widget.Button;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.VolleyLog;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;

public class ControlActivity extends AppCompatActivity {

    String url = "xxx.xxx.xxx.xxx";  // ESP8266's IP Address
    public String URL = "http://" + url;

    Button btnUp, btnDown;
    TextView tvIPAddress, tvStatus;

    @SuppressLint("ClickableViewAccessibility")
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_control);

        // get references
        btnUp = findViewById(R.id.buttonUp);
        btnDown = findViewById(R.id.buttonDown);
        tvIPAddress = findViewById(R.id.textViewIP);
        tvStatus = findViewById(R.id.textViewStatus);

        tvIPAddress.setText(url);

        btnUp.setOnTouchListener((view, motionEvent) -> {
            if(motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                tvStatus.setText(R.string.up);
                String url = URL + "/up";
                btnDown.setEnabled(false);
                StringRequest stringRequest = new StringRequest(Request.Method.GET, url, response -> {
                    Log.d("RESPONSE", response);
                }, error -> {
                    VolleyLog.d("ERROR", "Error: " + error.getMessage());
                });

                Volley.newRequestQueue((ControlActivity.this)).add(stringRequest);

                Volley.newRequestQueue(ControlActivity.this).add(stringRequest);
                return true;
            } else if(motionEvent.getAction() == MotionEvent.ACTION_UP) {
                tvStatus.setText(R.string.idle);
                String url = URL + "/idle";
                btnDown.setEnabled(true);
                StringRequest stringRequest = new StringRequest(Request.Method.GET, url, response -> {
                    Log.d("RESPONSE", response);
                }, error -> {
                    VolleyLog.d("ERROR", "Error: " + error.getMessage());
                });

                Volley.newRequestQueue(ControlActivity.this).add(stringRequest);
                return true;
            }
            return false;
        });

        btnDown.setOnTouchListener((view, motionEvent) -> {
            if(motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                tvStatus.setText(R.string.down);
                String url = URL + "/down";
                btnUp.setEnabled(false);
                StringRequest stringRequest = new StringRequest(Request.Method.GET, url, response -> {
                    Log.d("RESPONSE", response);
                }, error -> {
                    VolleyLog.d("ERROR", "Error: " + error.getMessage());
                });

                Volley.newRequestQueue(ControlActivity.this).add(stringRequest);
                return true;
            } else if(motionEvent.getAction() == MotionEvent.ACTION_UP) {
                tvStatus.setText(R.string.idle);
                String url = URL + "/idle";
                btnUp.setEnabled(true);
                StringRequest stringRequest = new StringRequest(Request.Method.GET, url, response -> {
                    Log.d("RESPONSE", response);
                }, error -> {
                    VolleyLog.d("ERROR", "Error: " + error.getMessage());
                });

                Volley.newRequestQueue(ControlActivity.this).add(stringRequest);
                return true;
            }
            return false;
        });
    }
}