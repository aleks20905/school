## linked-list callUp
##### Go Time ≈ 4061 ms [code](https://github.com/aleks20905/school/blob/main/benches/linkList/main.go)  / C++ Time ≈ 11243   ms [code](https://github.com/aleks20905/school/blob/main/benches/linkList/link.cpp)
- Доста интересно, има доста голяма разлика между времената, като и двата процеса бяха ``само на 1 thread``

> Двата кода работеха само на един тред, без да имат никаква специфично зададена паралелност, но учудващо Go натоварваше ядрото малко по-ефективно и на всеки няколко секунди ги редуваше.

- Ако рагледаме [графиките](https://docs.google.com/spreadsheets/d/12OKOfTIwt9B8t7XGaPYjhSUlAdayeMEGszysIuUacpU/edit?usp=sharing) можем да видим, че няма много разлика и двете решения растат линейно едно спрямо друго, като не се вижда да се разклоняват и двете решения следват една права и Go запазва постоянно 2.7x пъти по-бърз от C++ варианта.


##### Mem usage:

##### Go ≈ 1966 kb [Резултати](https://github.com/aleks20905/school/blob/main/benches/linkList_info/main_result)/[code](https://github.com/aleks20905/school/blob/main/benches/linkList_info/main.go) || C++ ≈ 3801 kb [Резултати](https://github.com/aleks20905/school/blob/main/benches/linkList_info/link_result)/[code](https://github.com/aleks20905/school/blob/main/benches/linkList_info/link.cpp) 

- Очакваше се Go да се справя много зле с използваната памет - учудващо е по-добре, но ``може да е проблемен начина за гледането на използваната памет``


> С толкова малко данни не се очаква да има проблеми и в двата кода, но ако се увеличат данните с драстично количество, след определено време се очаква Go да се запълни експоненциално много.





## linked-list-Mod
##### Go Time ≈ 7893 ms <[code](https://github.com/aleks20905/school/blob/main/benches/linkListModif/main.go)>  / C++ Time ≈ 12953 ms <[code](https://github.com/aleks20905/school/blob/main/benches/linkListModif/link.cpp)>
- Отново доста интересни резултати, пак има доста голяма разлика между времената, но изглежда, че и двата варианта са се забавили с еднакво количество. Като отново ``само на 1 thread`` и идентичno поведение както преди малко.


##### Mem usage:

##### Go ≈ 1835 - 6160 kb [Резултати](https://github.com/aleks20905/school/blob/main/benches/linkListModif/main_result)  /  C++ ≈ 3538 - 11272 kb [Резултати](https://github.com/aleks20905/school/blob/main/benches/linkListModif/link_result)

- Отново се очакваше Go да се справя много зле с използваната памет, но се справи по-добре дори от C++, ``но трябва да се има предивид че кода `НАРОЧНО НЕ` се освобождава памметта``- което забавя доста; 

-  `` Спрямо ``[графиките](https://docs.google.com/spreadsheets/d/12OKOfTIwt9B8t7XGaPYjhSUlAdayeMEGszysIuUacpU/edit#gid=1530631332)`` отново виждаме същото поведение`` 


## linked-list-Mod-Free_Mem
##### Go Time ≈ 285 ms <[code](https://github.com/aleks20905/school/blob/main/benches/linkListModif_freeMem/main.go)>  / C++ Time ≈ 518 ms <[code](https://github.com/aleks20905/school/blob/main/benches/linkListModif_freeMem/link.cpp)>

- След като започнахме да освобождаваме паметта, видяхме много голям скок в производителността, но отново Go повежда напред.
- Тук вече по-добре се виждаше силата на Go да храни нишките с данни много бързо. `` Go успяваше да държи 100% натоварване, като през определено време редуваше нишките, докато C++ падаше под 100% `` 


##### Mem usage:

##### Go ≈ 1703 - 5767 kb [Резултати](https://github.com/aleks20905/school/blob/main/benches/linkListModif_freeMem/main_result)  /  C++ ≈ 3538 - 3801 kb [Резултати](https://github.com/aleks20905/school/blob/main/benches/linkListModif_freeMem/link_result)


-  `` Спрямо ``[графиките](https://docs.google.com/spreadsheets/d/12OKOfTIwt9B8t7XGaPYjhSUlAdayeMEGszysIuUacpU/edit#gid=36193127)``можем да видим, че тук вече има голяма разлика между двата езика`` като след всяко минаване в C++ варианта се чистеха старите Nodes и държахме постоянен Mem usage. Но в Go варианта, дори да искаме да освобождаваме паметта, тя реално не е освободена, докато garbage collector-ът не мине да я затрие.



###### При `Windows` заменете ``getMemoryUsage()`` с показания код, Но данните ще се разминават много
c++
```c++
#include <windows.h>
#include <psapi.h>

size_t getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS_EX pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc))) {
        return pmc.WorkingSetSize;
    }
    cerr << "Error: Could not retrieve memory information." << endl;
    return 0;
}
```
Go 
```Go
func getMemoryUsage() uint64 {
    var mem runtime.MemStats
    runtime.ReadMemStats(&mem)
    return mem.Alloc
}

```