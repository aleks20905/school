## linked-list
##### Go Time ≈ 4061 ms [code](https://github.com/aleks20905/school/blob/main/benches/linkList/main.go)  / C++ Time ≈ 11243   ms [code](https://github.com/aleks20905/school/blob/main/benches/linkList/link.cpp)
> Доста интересно със сравнотелно еднакък код има доста голяма разлика между времената, но докато се учакваше Go да се справя много зле с изпoлзваната памет - учдващо не е чак толкова зле

##### Mem usage:

##### Go ≈ 1966 kb [Резултати](https://github.com/aleks20905/school/blob/main/benches/linkList_info/main_result)/[code](https://github.com/aleks20905/school/blob/main/benches/linkList_info/main.go) || C++ ≈ 3801 kb [Резултати](https://github.com/aleks20905/school/blob/main/benches/linkList_info/link_result)/[code](https://github.com/aleks20905/school/blob/main/benches/linkList_info/link.cpp) 

-като на данните от c++ не се вижда правилно това е бъг който не можах да го оправя

>Двата варианта работеха само на един тред, без да имат никаква паралелност, но учадващо сякаш Go натоварваше ядрото малко по ефективно през цялото време държеше 100% натоварване, докато при случая на C++ през цялото време беше около 99 
(направих няколко отита на Go да изчиля натоварването на процесо малко по детаилно но не успях да намеря подходящ tool без да влизам прекалено надълбоко с много сложни итежки 3th party код койдо да прави това )

> `` Ако рагледаме малко ``[графики](https://docs.google.com/spreadsheets/d/12OKOfTIwt9B8t7XGaPYjhSUlAdayeMEGszysIuUacpU/edit?usp=sharing)`` можеж да видим че няма много разлика и двете решения растът линейно спрямо количеството извиквания без да има bottleneck`` (но с толкова малко данни не се учаква да има проблеми, но ако се увеличат данните с много след определено време Go ще започне да се запабя драстично )




## linked-list-Mod
##### Go Time ≈ 7893 ms <[code](https://github.com/aleks20905/school/blob/main/benches/linkListModif/main.go)>  / C++ Time ≈ 12953 ms <[code](https://github.com/aleks20905/school/blob/main/benches/linkListModif/link.cpp)>
>Отново доста интересни резултати пак има доста голяма разлика между времената, отново учкваше се Go да се справя много зле с изпoлзваната памет, но се прави по добре дори от c++, ``Но трябва да се има предивид че кода `НАРОЧНО НЕ` се освобождава памметта``- което забавя доста; 
>Но се забеляза нещо доста интеренсо как Go без да има нищо специфично казано да прави multithreding имаше някаква нодка защото постепнно се меспетеше между ядрате едно след друго и ги редуваше

##### Mem usage:

##### Go ≈ 1835 - 6160 kb [Резултати](https://github.com/aleks20905/school/blob/main/benches/linkListModif/main_result)  /  C++ ≈ 3538 - 11272 kb [Резултати](https://github.com/aleks20905/school/blob/main/benches/linkListModif/link_result)

-като на данните от c++ не се вижда правилно това е бъг който не можах да го оправя

>Двата варианта работеха само на един тред, без да имат никаква паралелност, но учадващо сякаш Go натоварваше ядрото малко по ефективно през цялото време държеше 100% натоварване, докато при случая на C++ през цялото време беше около 99 
(направих няколко отита на Go да изчиля натоварването на процесо малко по детаилно но не успях да намеря подходящ tool без да влизам прекалено надълбоко с много сложни итежки 3th party код койдо да прави това )

> `` Ако рагледаме малко ``[графики](https://docs.google.com/spreadsheets/d/12OKOfTIwt9B8t7XGaPYjhSUlAdayeMEGszysIuUacpU/edit?usp=sharing)`` можеж да видим че няма много разлика и двете решения растът линейно спрямо количеството извиквания без да има bottleneck`` (но с толкова малко данни не се учаква да има проблеми, но ако се увеличат данните с много след определено време Go ще започне да се запабя драстично )


## linked-list-Mod-Free_Mem
##### Go Time ≈ 285 ms <[code](https://github.com/aleks20905/school/blob/main/benches/linkListModif/main.go)>  / C++ Time ≈ 518 ms <[code](https://github.com/aleks20905/school/blob/main/benches/linkListModif/link.cpp)>
>Отново доста интересни резултати пак има доста голяма разлика между времената, отново учкваше се Go да се справя много зле с изпoлзваната памет, но се прави по добре дори от c++, ``Но трябва да се има предивид че кода `НАРОЧНО НЕ` се освобождава памметта``- което забавя доста; 
>Но се забеляза нещо доста интеренсо как Go без да има нищо специфично казано да прави multithreding имаше някаква нодка защото постепнно се меспетеше между ядрате едно след друго и ги редуваше

##### Mem usage:

##### Go ≈ 1703 - 5767 kb [Резултати](https://github.com/aleks20905/school/blob/main/benches/linkListModif/main_result)  /  C++ ≈ 3538 - 3801 kb [Резултати](https://github.com/aleks20905/school/blob/main/benches/linkListModif/link_result)


> `` Ако рагледаме малко ``[графики](https://docs.google.com/spreadsheets/d/12OKOfTIwt9B8t7XGaPYjhSUlAdayeMEGszysIuUacpU/edit?usp=sharing)`` можеж да видим че няма много разлика и двете решения растът линейно спрямо количеството извиквания без да има bottleneck`` (но с толкова малко данни не се учаква да има проблеми, но ако се увеличат данните с много след определено време Go ще започне да се запабя драстично )



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