obsucura     <-- المجلد الرئيسي للمشروع (Root Directory)
│
├── bin/                        <-- (الملفات التنفيذية) Executable files 
│   └── app.exe                 <-- البرنامج النهائي بعد الترجمة (Compiled program)
│
├── include/                    <-- (ملفات الترويسة) Header files (.h)
│   ├── types.h                 <-- هنا نضع الـ Structs التي كتبناها في الخطوة السابقة
│   ├── linked_lists.h          <-- تعريفات دوال القوائم (Declarations)
│   ├── stacks_queues.h         <-- تعريفات دوال المكدسات والطوابير
│   ├── trees.h                 <-- تعريفات دوال الأشجار
│   ├── recursion.h             <-- تعريفات الدوال العودية (Recursive functions)
│   └── gui.h                   <-- تعريفات دوال الواجهة الرسومية
│
├── src/                        <-- (الأكواد المصدرية) Source files (.c)
│   ├── main.c                  <-- الدالة الرئيسية والقائمة (Main function & Menu)
│   ├── linked_lists.c          <-- برمجة دوال القوائم (Implementations)
│   ├── stacks_queues.c         <-- برمجة دوال المكدسات والطوابير
│   ├── trees.c                 <-- برمجة دوال الأشجار
│   ├── recursion.c             <-- برمجة الدوال العودية
│   └── file_parser.c           <-- الأكواد المسؤولة عن قراءة الملف النصي وتقسيمه
│
├── gui/                        <-- (الواجهة الرسومية) Graphical User Interface
│   └── gui_main.c              <-- أكواد مكتبة GTK+ أو Raylib (كما طلب الأستاذ)
│
├── data/                       <-- (قاعدة البيانات) Data files
│   └── history_data.txt        <-- الملف النصي الذي يحتوي على التواريخ والشخصيات
│
├── tests/                      <-- (الاختبارات) Test suite
│   └── test_main.c             <-- ملف لتجربة الدوال والتأكد من عملها (كما هو مطلوب في الـ PDF)
│
├── docs/                       <-- (التقارير) Documentation & Reports
│   └── Project_Report.pdf      <-- التقرير النهائي بصيغة PDF
│
└── Makefile                    <-- ملف لتسهيل عملية تجميع الكود (Compilation script)