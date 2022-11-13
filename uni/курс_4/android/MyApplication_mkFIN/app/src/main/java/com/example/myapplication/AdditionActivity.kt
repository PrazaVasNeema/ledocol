package com.example.myapplication

import android.app.Activity
import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import androidx.core.view.WindowCompat
import androidx.core.view.WindowInsetsCompat
import androidx.core.view.WindowInsetsControllerCompat
import java.text.ParseException
import java.text.SimpleDateFormat

private  const val TAG = "AdditionActivity"
private  const val SAVED_NAME = "1"
private  const val SAVED_SURNAME = "2"
private  const val SAVED_MIDDLE_NAME = "3"
private  const val SAVED_DATE = "4"
private  const val SAVED_FACU_NAME = "5"
private  const val SAVED_BUTTON_TEXT = "ButtonText"

class AdditionActivity : AppCompatActivity() {

    private lateinit var addition_EditTextName: TextView
    private lateinit var addition_EditTextSurname: TextView
    private lateinit var addition_EditTextMiddleName: TextView
    private lateinit var addition_EditTextDate: TextView
    private lateinit var addition_EditTextFacu: TextView
    private lateinit var additionButton: Button
    private var flag = false

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_addition)

        hideSystemUI()
        addition_EditTextName = findViewById(R.id.addition_EditTextName)
        addition_EditTextSurname = findViewById(R.id.addition_EditTextSurname)
        addition_EditTextMiddleName = findViewById(R.id.addition_EditTextMiddleName)
        addition_EditTextDate = findViewById(R.id.addition_EditTextDate)
        addition_EditTextFacu = findViewById(R.id.addition_EditTextFacu)
        additionButton = findViewById(R.id.additionButton)

        addition_EditTextName.text = savedInstanceState?.getString(SAVED_NAME)?:""
        addition_EditTextSurname.setText(savedInstanceState?.getString(SAVED_SURNAME)?:"")
        addition_EditTextMiddleName.setText(savedInstanceState?.getString(SAVED_MIDDLE_NAME)?:"")
        addition_EditTextDate.setText(savedInstanceState?.getString(SAVED_DATE)?:"")
        addition_EditTextFacu.setText(savedInstanceState?.getString(SAVED_FACU_NAME)?:"")

        val incomingBundle = intent.extras
        if (incomingBundle != null){
            val studentInfo = incomingBundle.getString("studentInfo")?.split(" ")
            val buttonTextEdit = incomingBundle.getString("buttonTextEdit")
            addition_EditTextName.text = studentInfo?.get(0) ?: ""
            addition_EditTextSurname.text = studentInfo?.get(1) ?: ""
            addition_EditTextMiddleName.text = studentInfo?.get(2) ?: ""
            addition_EditTextDate.text = studentInfo?.get(3) ?: ""
            addition_EditTextFacu.text = studentInfo?.get(4) ?: ""
            additionButton.text = buttonTextEdit?: "Добавить"
            flag = true
        }

        //https://zetcode.com/kotlin/regularexpressions/
        //https://stackoverflow.com/questions/42674717/regex-match-exactly-4-digits
        val nameRegex = "^[А-Яа-яA-Za-z]+$"
        val dateRegex = "^[0-9]{2}[/]+[0-9]{2}[/]+[0-9]{4}"
        val format = SimpleDateFormat("dd/MM/yyyy")

        additionButton.setOnClickListener {
            var errorFlag = false
            if (!nameRegex.toRegex().matches(addition_EditTextName.text)) {
                addition_EditTextName.error = getString(R.string.name_error)
                errorFlag = true
            }
            if (!nameRegex.toRegex().matches(addition_EditTextSurname.text)) {
                addition_EditTextSurname.error = getString(R.string.name_error)
                errorFlag = true
            }
            if (!nameRegex.toRegex().matches(addition_EditTextMiddleName.text)) {
                addition_EditTextMiddleName.error = getString(R.string.name_error)
                errorFlag = true
            }

            format.isLenient = false

            try {
                format.parse(addition_EditTextDate.text.toString())
                val temp = addition_EditTextDate.text.toString().split("/").toTypedArray()
                if(temp[2].toInt() < 1900 || temp[2].toInt() > 2022) {
                    addition_EditTextDate.error = getString(R.string.date_error)
                    errorFlag = true
                }
            } catch (e: ParseException) {
                            addition_EditTextDate.error = getString(R.string.date_error)
                            errorFlag = true
            }

//            when(dateRegex.toRegex().matches(addition_EditTextDate.text)){
//                false ->{
//                    addition_EditTextDate.error = getString(R.string.date_error)
//                    errorFlag = true
//                }
//                true -> {
//                    val temp = addition_EditTextDate.text.toString().split("/").toTypedArray()
//                    if (temp[0].toInt() < 1 || temp[0].toInt() > 31 ||
//                        temp[1].toInt() < 1 || temp[1].toInt() > 12 ||
//                        temp[2].toInt() < 1900 || temp[2].toInt() > 2022
//                    ) {
//                        addition_EditTextDate.error = getString(R.string.date_error)
//                        errorFlag = true
//                    }
//                }
//            }


            if (!nameRegex.toRegex().matches(addition_EditTextFacu.text)) {
                addition_EditTextFacu.error = getString(R.string.facu_error)
                errorFlag = true
            }

            if (!errorFlag) {
                val textToSend = addition_EditTextName.text.toString() + ' ' +
                        addition_EditTextSurname.text.toString() + ' ' +
                        addition_EditTextMiddleName.text.toString() + ' ' +
                        addition_EditTextDate.text.toString() + ' ' +
                        addition_EditTextFacu.text.toString()
                val intentResult = Intent().apply {
                    putExtra("newStudentInfo", textToSend)
                    putExtra("flag", flag)
                }
                Log.d(TAG, textToSend)
                setResult(Activity.RESULT_OK, intentResult)
                finish()
            }
        }

    }

override  fun onSaveInstanceState(savedInstanceState:Bundle){
    super.onSaveInstanceState(savedInstanceState)
    Log.i(TAG, "onSaveInstanceState")
    savedInstanceState.putString(SAVED_NAME, addition_EditTextName.text.toString())
    savedInstanceState.putString(SAVED_SURNAME, addition_EditTextSurname.text.toString())
    savedInstanceState.putString(SAVED_MIDDLE_NAME, addition_EditTextMiddleName.text.toString())
    savedInstanceState.putString(SAVED_DATE, addition_EditTextDate.text.toString())
    savedInstanceState.putString(SAVED_FACU_NAME, addition_EditTextFacu.text.toString())
    savedInstanceState.putString(SAVED_BUTTON_TEXT, additionButton.text.toString())
}

    private fun hideSystemUI() {
        WindowCompat.setDecorFitsSystemWindows(window, false)
        WindowInsetsControllerCompat(window,
            window.decorView.findViewById(android.R.id.content)).let { controller ->
            controller.hide(WindowInsetsCompat.Type.systemBars())
            controller.systemBarsBehavior = WindowInsetsControllerCompat.BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE
        }
    }
}
