## linked-list
##### Go Time ≈ 4061 ms [code](https://github.com/aleks20905/school/blob/main/benches/linkList/main.go)  / C++ Time ≈ 11243   ms [code](https://github.com/aleks20905/school/blob/main/benches/linkList/link.cpp)
> Доста интересно със сравнотелно еднакък код има доста голяма разлика между времената, но докато се учакваше Go да се справя много зле с изпoлзваната памет - учдващо не е чак толкова зле

##### Go mem usage≈ 152616 bytes [Резултати](https://github.com/aleks20905/school/blob/main/benches/linkList_info/main_result)/[code](https://github.com/aleks20905/school/blob/main/benches/linkList_info/main.go) || C++ mem usage≈ 131072 bytes [Резултати](https://github.com/aleks20905/school/blob/main/benches/linkList_info/link_result)/[code](https://github.com/aleks20905/school/blob/main/benches/linkList_info/link.cpp) 
-като на данните от c++ не се вижда правилно това е бъг който не можах да го оправя

>Двата варианта работеха само на един тред, без да имат никаква паралелност, но учадващо сякаш Go натоварваше ядрото малко по ефективно през цялото време държеше 100% натоварване, докато при случая на C++ през цялото време беше около 99 
(направих няколко отита на Go да изчиля натоварването на процесо малко по детаилно но не успях да намеря подходящ tool без да влизам прекалено надълбоко с много сложни итежки 3th party код койдо да прави това )
> `` Ако рагледаме малко ``[графики](https://docs.google.com/spreadsheets/d/12OKOfTIwt9B8t7XGaPYjhSUlAdayeMEGszysIuUacpU/edit?usp=sharing)`` можеж да видим че няма много разлика и двете решения растът линейно спрямо количеството извиквания без да има bottleneck`` (но с толкова малко данни не се учаква да има проблеми, но ако се увеличат данните с много след определено време Go ще започне да се запабя драстично )
