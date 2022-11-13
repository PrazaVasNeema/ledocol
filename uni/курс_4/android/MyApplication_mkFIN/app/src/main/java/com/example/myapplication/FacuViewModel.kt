package com.example.myapplication

import android.util.Log
import androidx.lifecycle.ViewModel

private  const val TAG = "FacuViewModel"

class FacuViewModel: ViewModel() {

    var FacuBank: List<Facu> = listOf(
        Facu("Все факультеты")
    )
    var currentIndex = 0

    val currentFacuName: String
        get() = FacuBank[currentIndex].facuName

    fun moveToNext() {
        currentIndex = (currentIndex + 1) % FacuBank.size
    }

    fun moveToPrev() {
        currentIndex = (FacuBank.size + currentIndex - 1) % FacuBank.size
    }

    fun addFacu(facuName: String) {
        if (!FacuBank.contains(Facu(facuName))) {
            FacuBank += Facu(facuName)
        }
        Log.d(TAG, FacuBank[currentIndex].facuName)
    }

    fun removeFacu(facuName: String) {
        for (i in FacuBank.indices) {
            if (FacuBank[i].facuName == facuName) {
                var temp = FacuBank.toMutableList()
                temp.removeAt(i)
                FacuBank = temp.toList()
                break
            }
        }
        if(currentIndex != 0)
            moveToPrev()
    }

    fun clearFacu() {
        FacuBank = listOf(
            Facu("Все факультеты")
        )
        currentIndex = 0
    }

    fun logFun() {
        for (i in FacuBank.indices) {
            Log.d("MainActivity", FacuBank[i].facuName)
        }
    }

    fun setFacuNeededIndex(facuNameNeeded: String) {
        for (i in FacuBank.indices) {
            if (FacuBank[i].facuName == facuNameNeeded) {
                currentIndex = i
                return
            }
        }
    }
}