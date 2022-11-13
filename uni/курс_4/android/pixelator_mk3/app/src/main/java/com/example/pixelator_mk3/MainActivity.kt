package com.example.pixelator_mk3

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Handler
import android.view.View
import android.view.WindowManager
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import androidx.core.view.WindowCompat
import androidx.core.view.WindowInsetsCompat
import androidx.core.view.WindowInsetsControllerCompat
import kotlin.math.roundToInt

class MainActivity : AppCompatActivity() {

    private lateinit var et_input: EditText
    private lateinit var tv_value_tbc: TextView
    private lateinit var tv_operator: TextView
    private var operationState = 0


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        hideSystemUI()

        setContentView(R.layout.activity_main)

        et_input = findViewById(R.id.editText_input)
        et_input.setText("")
        tv_value_tbc = findViewById(R.id.textView_value_to_be_changed)
        tv_value_tbc.text = ""
        tv_operator = findViewById(R.id.textView_operator)
        tv_operator.text = ""
        findViewById<Button>(R.id.num_1).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_2).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_3).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_4).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_5).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_6).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_7).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_8).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_9).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_0).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_plus).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_minus).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_mult).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_div).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_eq).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.num_c).setOnClickListener { onPanelClick((it as Button)) }
        findViewById<Button>(R.id.button_point).setOnClickListener { onPanelClick((it as Button)) }
    }
    private fun onPanelClick(view: View?) {
        when (view?.id?: return) {
            R.id.num_1 -> {
                et_input.append("1")
            }
            R.id.num_2 -> {
                et_input.append("2")
            }
            R.id.num_3 -> {
                et_input.append("3")
            }
            R.id.num_4 -> {
                et_input.append("4")
            }
            R.id.num_5 -> {
                et_input.append("5")
            }
            R.id.num_6-> {
                et_input.append("6")
            }
            R.id.num_7-> {
                et_input.append("7")
            }
            R.id.num_8-> {
                et_input.append("8")
            }
            R.id.num_9-> {
                et_input.append("9")
            }
            R.id.num_0 -> {
                et_input.append("0")
            }
            R.id.num_plus-> {
                blackBoxMagic('+')
            }
            R.id.num_minus-> {
                blackBoxMagic('-')
            }
            R.id.num_mult-> {
                blackBoxMagic('*')
            }
            R.id.num_div-> {
                blackBoxMagic('/')
            }
            R.id.button_point-> {
                if(!et_input.text.toString().contains('.') && !et_input.text.toString().isEmpty())
                    et_input.append(".")
            }
            R.id.num_eq-> {
                if(tv_value_tbc.text == "")
                    return
                if(et_input.text.toString() == ""){
                    et_input.setText(tv_value_tbc.text)
                    tv_value_tbc.text = ""
                    tv_operator.text = ""
                }
                else{
                    when(tv_operator.text.toString()){
                        "+" ->{
                            et_input.setText((tv_value_tbc.text.toString().toDouble().plus
                                (et_input.text.toString().toDouble())).toString())
                        }
                        "-" ->{
                            et_input.setText((tv_value_tbc.text.toString().toDouble().minus
                                (et_input.text.toString().toDouble())).toString())
                        }
                        "*" ->{
                            et_input.setText((tv_value_tbc.text.toString().toDouble() *
                                et_input.text.toString().toDouble()).toString())
                        }
                        "/" ->{
                            (et_input.setText((tv_value_tbc.text.toString().toDouble() /
                                    et_input.text.toString().toDouble()).toString()))
                        }
                    }
                    tv_value_tbc.text = ""
                    tv_operator.text = ""
                }
                operationState = 0
            }
            R.id.num_c-> {
                et_input.setText("")
                tv_value_tbc.text = ""
                tv_operator.text = ""
                operationState = 0
            }
        }
    }

    private fun blackBoxMagic(chr: Char){
        if(operationState == 0){
            if(et_input.text.toString() == "")
                return
            tv_value_tbc.text = et_input.text.toString()
            tv_operator.text = chr.toString()
            et_input.setText("")
            operationState = 1
        }
        else{
            if(et_input.text.toString() != "") {
                when (tv_operator.text.toString()) {
                    "+" -> {
                        tv_value_tbc.text =
                            (tv_value_tbc.text.toString().toDouble().plus
                                (et_input.text.toString().toDouble())).toString()
                    }
                    "-" -> {
                        tv_value_tbc.text =
                            (tv_value_tbc.text.toString().toDouble().minus
                                (et_input.text.toString().toDouble())).toString()
                    }
                    "*" -> {
                        tv_value_tbc.text =
                            (tv_value_tbc.text.toString().toDouble() *
                                    et_input.text.toString().toDouble()).toString()
                    }
                    "/" -> {
                        tv_value_tbc.text =
                            (tv_value_tbc.text.toString().toDouble() /
                                    et_input.text.toString().toDouble()).toString()
                    }
                }
                et_input.setText("")
            }
            tv_operator.text = chr.toString()
        }
    }

    private fun hideSystemUI() {
        WindowCompat.setDecorFitsSystemWindows(window, false)
        WindowInsetsControllerCompat(window,
            window.decorView.findViewById(android.R.id.content)).let { controller ->
            controller.hide(WindowInsetsCompat.Type.systemBars())

            // When the screen is swiped up at the bottom
            // of the application, the navigationBar shall
            // appear for some time
            controller.systemBarsBehavior = WindowInsetsControllerCompat.BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE
        }
    }
    private fun pointCheck(){
        val str1 = findViewById<EditText>(R.id.editText_input).text
    }
}