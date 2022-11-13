package com.example.myapplication

import android.app.Activity
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.activity.result.contract.ActivityResultContracts
import androidx.core.view.WindowCompat
import androidx.core.view.WindowInsetsCompat
import androidx.core.view.WindowInsetsControllerCompat
import androidx.lifecycle.ViewModelProvider

private  const val TAG = "MainActivity"
private const val  KEY_INDEX_STUDENT = "index"
private const val  KEY_INDEX_FACU = "index"

class MainActivity : AppCompatActivity() {

    private  lateinit var studentButtonNext : Button
    private  lateinit var studentButtonPrev : Button
    private  lateinit var studentButtonAdd : Button
    private  lateinit var studentButtonRemove : Button
    private  lateinit var studentButtonEdit : Button
    private  lateinit var studentTextViewName : TextView
    private  lateinit var studentTextViewMiddleName : TextView
    private  lateinit var studentTextViewSurname : TextView
    private  lateinit var studentTextViewDate: TextView
    private  lateinit var facuButtonNext : Button
    private  lateinit var facuButtonPrev : Button
    private  lateinit var facuTextViewName : TextView
    private  var moveToNextFlag: Boolean = true
    private  lateinit var errorStudent : TextView

    private  val StudentViewModelInstance:StudentViewModel by lazy{
        val provider = ViewModelProvider(this)
        provider.get(StudentViewModel::class.java)
    }
    private  val FacuViewModelInstance:FacuViewModel by lazy{
        val provider = ViewModelProvider(this)
        provider.get(FacuViewModel::class.java)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        StudentViewModelInstance.currentIndex = savedInstanceState?.getInt(KEY_INDEX_STUDENT)?:0
        FacuViewModelInstance.currentIndex = savedInstanceState?.getInt(KEY_INDEX_FACU)?:0

        if(StudentViewModelInstance.StudentBank.isEmpty()){
            StudentViewModelInstance.addStudent("testName", "testMiddleName", "testSurname", "01/01/2000", "testFacu")
            FacuViewModelInstance.addFacu(StudentViewModelInstance.currentStudentFacuName)
            StudentViewModelInstance.addStudent("testNameSecond", "testMiddleNameSecond", "testSurnameSecond", "12/12/1955", "testFacu")
            FacuViewModelInstance.addFacu(StudentViewModelInstance.currentStudentFacuName)
        }

        hideSystemUI()
        studentButtonNext = findViewById(R.id.studentButtonNext)
        studentButtonPrev = findViewById(R.id.studentButtonPrev)
        studentButtonAdd = findViewById(R.id.studentButtonAdd)
        studentButtonRemove = findViewById(R.id.studentButtonRemove)
        studentButtonEdit = findViewById(R.id.studentButtonEdit)
        studentTextViewName = findViewById(R.id.studentTextViewSurname)
        studentTextViewMiddleName = findViewById(R.id.studentTextViewMiddleName)
        studentTextViewSurname = findViewById(R.id.studentTextViewName)
        studentTextViewDate = findViewById(R.id.studentTextViewDate)
        facuButtonNext = findViewById(R.id.facuButtonNext)
        facuButtonPrev = findViewById(R.id.facuButtonPrev)
        facuTextViewName = findViewById(R.id.facuTextViewName)
        errorStudent = findViewById(R.id.errorStudent)

        studentButtonNext.setOnClickListener{
            if(StudentViewModelInstance.StudentBank.isNotEmpty()) {
                StudentViewModelInstance.moveToNext()
                moveToNextFlag = true
                updateStudent()
            }
        }
        studentButtonPrev.setOnClickListener{
            if(StudentViewModelInstance.StudentBank.isNotEmpty()) {
                StudentViewModelInstance.moveToPrev()
                moveToNextFlag = false
                updateStudent()
            }
        }

        val resultLauncherAdd = registerForActivityResult(ActivityResultContracts.StartActivityForResult()){
                result ->
            if (result.resultCode == Activity.RESULT_OK){
                val data: Intent? = result.data
                val studentDataTransfer = data?.getStringExtra("newStudentInfo")?.split(" ")
                    ?.toTypedArray()
                StudentViewModelInstance.addStudent(studentDataTransfer?.get(0) ?: "",studentDataTransfer?.get(1) ?: "",
                    studentDataTransfer?.get(2) ?: "",studentDataTransfer?.get(3) ?: "",studentDataTransfer?.get(4) ?: "")
                FacuViewModelInstance.addFacu(studentDataTransfer?.get(4) ?: "")
                StudentViewModelInstance.currentIndex = StudentViewModelInstance.StudentBank.size - 1
//                updateStudent()
//                FacuViewModelInstance.currentIndex = 0
                FacuViewModelInstance.setFacuNeededIndex(studentDataTransfer?.get(4) ?: "")
                updateFacu()
            }
        }
        studentButtonAdd.setOnClickListener{
            val intent = Intent(this, AdditionActivity::class.java)
            resultLauncherAdd.launch(intent)
        }

        studentButtonRemove.setOnClickListener{
            if(StudentViewModelInstance.StudentBank.isNotEmpty()) {
                val facuName = StudentViewModelInstance.currentStudentFacuName
                StudentViewModelInstance.removeStudent(facuName)
                val facuRelevantStudentCount = StudentViewModelInstance.removeStudentFacuRemainderCheck(facuName)

                if (facuRelevantStudentCount == 0)
                    FacuViewModelInstance.removeFacu(facuName)
                if(facuRelevantStudentCount == 1)
                    errorStudent.text = "Единственный студент!"
                if(StudentViewModelInstance.removeStudentFacuRemainderCheckAllFacuEdition() == 1)
                    errorStudent.text = "Единственный студент"
                moveToNextFlag = false
                updateFacu()
            }
        }


        val resultLauncherEdit = registerForActivityResult(ActivityResultContracts.StartActivityForResult()){
                result ->
            if (result.resultCode == Activity.RESULT_OK){
                val data: Intent? = result.data
                val studentDataTransfer = data?.getStringExtra("newStudentInfo")?.split(" ")
                    ?.toTypedArray()
                val tempFacuName = StudentViewModelInstance.currentStudentFacuName

                FacuViewModelInstance.addFacu(studentDataTransfer?.get(4) ?: "")
                //Log.d(TAG, studentDataTransfer?.get(4) ?: "")
                StudentViewModelInstance.editStudent(
                    Student(studentDataTransfer?.get(0) ?: "",studentDataTransfer?.get(1) ?: "",
                    studentDataTransfer?.get(2) ?: "",studentDataTransfer?.get(3) ?: "",studentDataTransfer?.get(4) ?: ""))
                if (StudentViewModelInstance.removeStudentFacuRemainderCheck(tempFacuName) == 0) {
                    FacuViewModelInstance.removeFacu(tempFacuName)
                }
                FacuViewModelInstance.setFacuNeededIndex(studentDataTransfer?.get(4) ?: "")
                updateFacu()
                FacuViewModelInstance.logFun()
            }
        }

        studentButtonEdit.setOnClickListener {
            if(StudentViewModelInstance.StudentBank.isNotEmpty()) {
                val intent = Intent(this, AdditionActivity::class.java)
                intent.putExtra("studentInfo", StudentViewModelInstance.currentStudentInfoAll)
                intent.putExtra("buttonTextEdit", "Изменить")
                resultLauncherEdit.launch(intent)
            }
        }
        facuButtonNext.setOnClickListener{
            if(FacuViewModelInstance.FacuBank.isNotEmpty()) {
                FacuViewModelInstance.moveToNext()
                updateFacu()
            }
        }
        facuButtonPrev.setOnClickListener{
            if(FacuViewModelInstance.FacuBank.isNotEmpty()) {
                FacuViewModelInstance.moveToPrev()
                updateFacu()
            }
        }
        updateFacu()
    }

    private  fun updateStudent(){
        var currentIndex = StudentViewModelInstance.currentIndex
        if(!(FacuViewModelInstance.currentFacuName == "Все факультеты")) {
            while (StudentViewModelInstance.StudentBank[currentIndex].facu != FacuViewModelInstance.currentFacuName) {
                if(moveToNextFlag)
                    StudentViewModelInstance.moveToNext()
                else
                    StudentViewModelInstance.moveToPrev()
                currentIndex = StudentViewModelInstance.currentIndex
            }
        }
        val studentFIO = StudentViewModelInstance.currentStudentFIO.split(" ")
        val studentDate = StudentViewModelInstance.currentStudentDate
        studentTextViewName.text = studentFIO[0]
        studentTextViewMiddleName.text = studentFIO[1]
        studentTextViewSurname.text = studentFIO[2]
        studentTextViewDate.text = studentDate
        if(!(FacuViewModelInstance.currentFacuName == "Все факультеты"))
            facuTextViewName.text = StudentViewModelInstance.currentStudentFacuName
        val facuNamee = facuTextViewName.text

        if (facuNamee == "Все факультеты" ||
                    StudentViewModelInstance.removeStudentFacuRemainderCheck(StudentViewModelInstance.currentStudentFacuName) > 1){
            errorStudent.text = ""
        }
        if(facuNamee != "Все факультеты" &&
            StudentViewModelInstance.removeStudentFacuRemainderCheck(StudentViewModelInstance.currentStudentFacuName) == 1)
            errorStudent.text = "Единственный студент"
        if(StudentViewModelInstance.removeStudentFacuRemainderCheckAllFacuEdition() == 1)
            errorStudent.text = "Единственный студент"
    }
    private  fun updateFacu(){
        facuTextViewName.text = FacuViewModelInstance.currentFacuName
        if(StudentViewModelInstance.StudentBank.isNotEmpty())
            updateStudent()
        else{
            studentTextViewName.text = "..."
            studentTextViewMiddleName.text = "..."
            studentTextViewSurname.text = "..."
            studentTextViewDate.text = "../../...."
        }
    }

    override  fun onSaveInstanceState(savedInstanceState:Bundle){
        super.onSaveInstanceState(savedInstanceState)
        savedInstanceState.putInt(KEY_INDEX_STUDENT, StudentViewModelInstance.currentIndex)
        savedInstanceState.putInt(KEY_INDEX_FACU, FacuViewModelInstance.currentIndex)
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