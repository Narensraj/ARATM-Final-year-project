using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WaitForTime : MonoBehaviour
{
    void Start(){
        StartCoroutine(Test ());
    }
        IEnumerator Test(){
            yield return new WaitForSeconds(10);
        }
 }