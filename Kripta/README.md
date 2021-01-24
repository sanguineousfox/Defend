# Welcome to StackEdit!

Hi! I'm your first Markdown file in **StackEdit**. If you want to learn about StackEdit, you can read me. If you want to play with Markdown, you can edit me. Once you have finished with me, you can create new files by opening the **file explorer** on the left corner of the navigation bar.


# Files

StackEdit stores your files in your browser, which means all your files are automatically saved locally and are accessible **offline!**

## Create files and folders

The file explorer is accessible using the button in left corner of the navigation bar. You can create a new file by clicking the **New file** button in the file explorer. You can also create folders by clicking the **New folder** button.

## Switch to another file

All your files and folders are presented as a tree in the file explorer. You can switch from one to another by clicking a file in the tree.

## Rename a file

You can rename the current file by clicking the file name in the navigation bar or by clicking the **Rename** button in the file explorer.

## Delete a file

You can delete the current file by clicking the **Remove** button in the file explorer. The file will be moved into the **Trash** folder and automatically deleted after 7 days of inactivity.

## Export a file

You can export the current file by clicking **Export to disk** in the menu. You can choose to export the file as plain Markdown, as HTML using a Handlebars template or as a PDF.


# Synchronization

Synchronization is one of the biggest features of StackEdit. It enables you to synchronize any file in your workspace with other files stored in your **Google Drive**, your **Dropbox** and your **GitHub** accounts. This allows you to keep writing on other devices, collaborate with people you share the file with, integrate easily into your workflow... The synchronization mechanism takes place every minute in the background, downloading, merging, and uploading file modifications.

There are two types of synchronization and they can complement each other:

- The workspace synchronization will sync all your files, folders and settings automatically. This will allow you to fetch your workspace on any other device.
	> To start syncing your workspace, just sign in with Google in the menu.

- The file synchronization will keep one file of the workspace synced with one or multiple files in **Google Drive**, **Dropbox** or **GitHub**.
	> Before starting to sync files, you must link an account in the **Synchronize** sub-menu.

## Open a file

You can open a file from **Google Drive**, **Dropbox** or **GitHub** by opening the **Synchronize** sub-menu and clicking **Open from**. Once opened in the workspace, any modification in the file will be automatically synced.

## Save a file

You can save any file of the workspace to **Google Drive**, **Dropbox** or **GitHub** by opening the **Synchronize** sub-menu and clicking **Save on**. Even if a file in the workspace is already synced, you can save it to another location. StackEdit can sync one file with multiple locations and accounts.

## Synchronize a file

Once your file is linked to a synchronized location, StackEdit will periodically synchronize it by downloading/uploading any modification. A merge will be performed if necessary and conflicts will be resolved.

If you just have modified your file and you want to force syncing, click the **Synchronize now** button in the navigation bar.

> **Note:** The **Synchronize now** button is disabled if you have no file to synchronize.

## Manage file synchronization

Since one file can be synced with multiple locations, you can list and manage synchronized locations by clicking **File synchronization** in the **Synchronize** sub-menu. This allows you to list and remove synchronized locations that are linked to your file.


# Publication

Publishing in StackEdit makes it simple for you to publish online your files. Once you're happy with a file, you can publish it to different hosting platforms like **Blogger**, **Dropbox**, **Gist**, **GitHub**, **Google Drive**, **WordPress** and **Zendesk**. With [Handlebars templates](http://handlebarsjs.com/), you have full control over what you export.

> Before starting to publish, you must link an account in the **Publish** sub-menu.

## Publish a File

You can publish your file by opening the **Publish** sub-menu and by clicking **Publish to**. For some locations, you can choose between the following formats:

- Markdown: publish the Markdown text on a website that can interpret it (**GitHub** for instance),
- HTML: publish the file converted to HTML via a Handlebars template (on a blog for example).

## Update a publication

After publishing, StackEdit keeps your file linked to that publication which makes it easy for you to re-publish it. Once you have modified your file and you want to update your publication, click on the **Publish now** button in the navigation bar.

> **Note:** The **Publish now** button is disabled if your file has not been published yet.

## Manage file publication

Since one file can be published to multiple locations, you can list and manage publish locations by clicking **File publication** in the **Publish** sub-menu. This allows you to list and remove publication locations that are linked to your file.


# Markdown extensions

StackEdit extends the standard Markdown syntax by adding extra **Markdown extensions**, providing you with some nice features.

> **ProTip:** You can disable any **Markdown extension** in the **File properties** dialog.


## SmartyPants

SmartyPants converts ASCII punctuation characters into "smart" typographic punctuation HTML entities. For example:

|                |ASCII                          |HTML                         |
|----------------|-------------------------------|-----------------------------|
|Single backticks|`'Isn't this fun?'`            |'Isn't this fun?'            |
|Quotes          |`"Isn't this fun?"`            |"Isn't this fun?"            |
|Dashes          |`-- is en-dash, --- is em-dash`|-- is en-dash, --- is em-dash|


## KaTeX

You can render LaTeX mathematical expressions using [KaTeX](https://khan.github.io/KaTeX/):

The *Gamma function* satisfying $\Gamma(n) = (n-1)!\quad\forall n\in\mathbb N$ is via the Euler integral

$$
\Gamma(z) = \int_0^\infty t^{z-1}e^{-t}dt\,.
$$

> You can find more information about **LaTeX** mathematical expressions [here](http://meta.math.stackexchange.com/questions/5020/mathjax-basic-tutorial-and-quick-reference).


## UML diagrams


# Квадрат Полибия - исследование и криптоанализ

## Содержание
1. [Описание шифра](#cipher_description)
1. [Криптоанализ](#cryptanalysis)
1. [Результаты](#result)
1. [Использование](#использование)
1. [Материалы](#materials)

<a name="cipher_description" />Описание шифра

«Квадрат Полибия» представляет собой квадрат 5×6, столбцы и строки которого нумеруются цифрами от 1 до 6. В каждую клетку этого квадрата записывается одна буква (в нашем алфавите 31  в одну клетку поместите буквы  и-й, ь-ъ, у-ё). Буквы расположены в алфавитном порядке. 

Алфавит - "АБВГДЕЖЗИКЛМНОПРСТУФХЦЧШЩЫЬЭЮЯ"

Ключевое слово - "АБВГДЕ". 

Тогда наш ключ примет следующий вид:

|А|Б|В|Г|Д|Е|
|-|-|-|-|-|-|-|-|
|**Ж**|**З**|**И-Й**|**К**|**Л**|**М**|
|**Н**|**О**|***П****|**Р**|**С**|**Т**|
|**У**|**Ф**|***Х****|**Ц**|**Ч**|**Ш**|
|**Щ**|**Ы**|**Ь-Ъ**|**Э**|**Ю**|**Я**|

Для создание качественного шифра нужно циклично сместить алфавит влево или вправо.

Правила шифрования

Производится циклическое смещение алфавита.
После смещения выбирается направление шифрования от строки вверх или вниз, от столбца влево или вправо.
Буквы в тексте заменяются на соответствующие буквы(соседи по направлению).

Рассмотрим на примере.

Допустим, мы хотим зашифровать сообщение (не смещая алфавит) “”Тройное клацанье” КОРОЛЕВА”

Для того, чтобы зашифровать сообщение, необходимо задать направление смещение. 
Заменяем все буквы и шифруемого текста, на буквы находящиеся строчкой ниже.
Получаем зашифрованный текст (Знаки препинания и регистр не учитываются) -
“”Шцфпуфм рсжэжуву” Рфцфсмиж”

Мы зашифровали тайное послание для членов культа.

## <a name="cryptanalysis" />Криптоанализ

Для криптоанализа использовалась статистика употребления букв в тексте.
согласно статистике  самые часто упртребляемые буквы в руской речи это: 

| о-1 | е-2 | а-3 | и-4 |...


Согласно этой глобальной статистики, мы можем предполагать, что буквы которых будет больше всего в тексте будут относиться к лидерам статистики.

В результате разницы между позицией предполагаемой буквы и лидером (собираемой статистики из зашифрованного текста) мы узнаем количество шагов смещения и направление. Следовательно можем провести пробную дешифрацию текста, которая будет верна в большинстве случаев. Если же дешифровка текста не удовлетворяет нашим требованиям мы можем повторить ее со следующей строчкой рейтинга глобальной статистики.  


## <a name= "result" /> Результаты  

1 - При запуске программы нас встречает меню которое предлагает нам выбрать режим работы .

Если вверху надпись “Файл не готов к работе ” то это означает что файл пуст и не может быть зашифрован/дешифрован.
(Файлы создаются на диске D)
C0D3D_OUT.TXT - рабочий файл

! [] (res1.png

Готов к работе!!

! [] (res2.png)

Если выбрать режим шифрования программа предложит выполнить сдвиг алфавита

! [] (res3.png)

теперь зашифрованный текст записан в файл _C0D3D_IN.txt.

Для повторного сдвига необходимо повторить процесс.

! [] (res4.png)

Для дешифрации необходимо перейти во 2 пункт меню.
Стоит помнить что текст может быть не расшифрован с первого раза для этого в меню предусмотрена функция повторной дешифрации.

До дешифрации 

! [] (res5.png)
При дешифрации текста стоит помнить, что чем больше текст тем проще программе будет его расшифровать 

После
! [] (res6.png)

Данные сохраняются в файл _C0D3D_OUT.TXT


## <a name= "использование" /> Использование   

WordCount() - осуществляет подсчет статистики в тексте (шифрованном), на ее основе потом будет выполнена дешифрация. 

FileWrite(),FileWipe(),FileRead(),FileEncoding() - функции для работы с файлами.

WordShift() - функция шифрования/дешифрования (заменяет символы в тексте) зависит mod 

ArrayDecoding() - генерирует ключ (смещая исходную маску на разницу в значениях)

MostCommonWord() - выводит статистику на экран.

ShiftDecription() - выводит расшифрованный  текст на экран, для проверки пользователем







## <a name= "материалы" /> Материалы  

[Частотность  ] [1]

[Квадрат Полибия] [2]


[1]:
https://ru.wikipedia.org/wiki/%D0%A7%D0%B0%D1%81%D1%82%D0%BE%D1%82%D0%BD%D0%BE%D1%81%D1%82%D1%8C

[2]:
https://ru.wikipedia.org/wiki/%D0%9A%D0%B2%D0%B0%D0%B4%D1%80%D0%B0%D1%82_%D0%9F%D0%BE%D0%BB%D0%B8%D0%B1%D0%B8%D1%8F#:~:text=%D0%A1%D0%BF%D0%BE%D1%81%D0%BE%D0%B1%20%D1%88%D0%B8%D1%84%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D1%8F,-%D0%9D%D0%B5%D1%81%D0%BC%D0%BE%D1%82%D1%80%D1%8F%20%D0%BD%D0%B0%20%D1%82%D0%BE&text=%D0%91%D0%B5%D1%80%D1%83%D1%82%D1%81%D1%8F%20%D0%B4%D0%B2%D0%B0%20%D1%86%D0%B5%D0%BB%D1%8B%D1%85%20%D1%87%D0%B8%D1%81%D0%BB%D0%B0%2C%20%D0%BF%D1%80%D0%BE%D0%B8%D0%B7%D0%B2%D0%B5%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5,%D0%BF%D0%BE%20%D0%BE%D0%B4%D0%BD%D0%BE%D0%B9%20%D0%B2%20%D0%BA%D0%B0%D0%B6%D0%B4%D1%83%D1%8E%20%D0%BA%D0%BB%D0%B5%D1%82%D0%BA%D1%83.




