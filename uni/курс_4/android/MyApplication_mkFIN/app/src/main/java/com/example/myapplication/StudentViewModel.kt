    package com.example.myapplication

import android.util.Log
import androidx.lifecycle.ViewModel
import java.lang.Math.abs

private  const val TAG = "StudentViewModel"

class StudentViewModel: ViewModel() {
    init{
        Log.d(TAG, "ViewModel instance created")
    }
    override  fun onCleared(){
        super.onCleared()
        Log.d(TAG, "ViewModel instance is about to be destroyed")
    }
    var StudentBank: List<Student> = listOf()
    var currentIndex = 0

    val currentStudentFIO: String
        get() = StudentBank[currentIndex].surname + ' ' +
                StudentBank[currentIndex].middleName + ' ' +
                StudentBank[currentIndex].name

    val currentStudentDate: String
        get() = StudentBank[currentIndex].date

    val currentStudentFacuName: String
        get() = StudentBank[currentIndex].facu

    val currentStudentInfoAll: String
        get() = "$currentStudentFIO $currentStudentDate $currentStudentFacuName"

    fun  moveToNext(){
        currentIndex = (currentIndex + 1) % StudentBank.size
    }

    fun moveToPrev(){
        currentIndex = (StudentBank.size + currentIndex - 1) % StudentBank.size
        Log.d(TAG, currentIndex.toString())
    }
    fun addStudent(name: String, surname: String, middleName: String, date: String, facu: String){
        StudentBank += Student(name, surname, middleName, date, facu)
        Log.d(TAG, currentStudentFIO)
    }
    fun removeStudent(facuName: String){
        Log.d(TAG, StudentBank.size.toString())
        var temp = StudentBank.toMutableList()
        temp.removeAt(currentIndex)
        StudentBank = temp.toList()
        Log.d(TAG, StudentBank.size.toString())
        if(currentIndex != 0)
            moveToPrev()
    }
    fun removeStudentFacuRemainderCheck(facuName: String) : Int{
        var studentCount = 0
        for (i in StudentBank.indices){
            if (StudentBank[i].facu == facuName){
                studentCount += 1
            }
        }
        return studentCount
    }

    fun removeStudentFacuRemainderCheckAllFacuEdition() : Int{
        var studentCount = 0
        for (i in StudentBank.indices){
                studentCount += 1
        }
        return studentCount
    }

    fun clearStudents(){
        StudentBank = listOf()
    }
    fun editStudent(newStudentInfo: Student){
        StudentBank[currentIndex].name = newStudentInfo.name
        StudentBank[currentIndex].middleName = newStudentInfo.middleName
        StudentBank[currentIndex].surname = newStudentInfo.surname
        StudentBank[currentIndex].date = newStudentInfo.date
        StudentBank[currentIndex].facu = newStudentInfo.facu

    }
}