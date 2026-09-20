OHH, nah ini baru jelas 😄. Berarti **load cell 50 kg kamu sebenarnya cuma punya 3 kabel: merah, putih, hitam**, lalu kamu membuat konfigurasi **pseudo/full-bridge dengan 2 resistor eksternal**.

Jadi rangkaiannya kira-kira begini:

```text
                 LOAD CELL 50 KG
                   
                    MERAH
                      │
                      ▼
                     E+
                     
        PUTIH ────────┬──────── A+
                      │
                      R1
                      │
                      ├─────────┐
                      │         │
        HITAM ────────┬──────── E-
                      │
                      R2
                      │
                      └──────── A-
```

Tapi dari penjelasanmu, lebih tepatnya:

```text
PUTIH ─────────────── A+
  │
  └── R1 ───────┐
                │
                ├──── A-
                │
  ┌── R2 ───────┘
  │
HITAM ─────────────── E-

MERAH ─────────────── E+
```

**Nah ini penting:** kalau resistor yang kamu gunakan sebenarnya **400 kΩ**, sedangkan contoh rangkaian menggunakan **1 kΩ**, maka nilainya **beda sangat jauh**.

### 400 kΩ vs 1 kΩ

400 kΩ = **400.000 Ω**

Sedangkan 1 kΩ = **1.000 Ω**

Jadi:

**400 kΩ = 400× lebih besar daripada 1 kΩ.**

Akibatnya pembagian tegangan pada bridge menjadi sangat berbeda dan HX711 bisa mendapatkan sinyal yang sangat kecil/tidak sesuai.

genui{"learning_viz":{"type_id":"RESISTORS_IN_SERIES_EQUIVALENT","initial_values":{"r1":1000,"r2":1000,"voltage":5},"locale_override":"id-ID"}}

### Tapi ada satu hal yang perlu kita pastikan

Kamu sebelumnya mengukur:

* Black ↔ White = **623 Ω**
* Black ↔ Yellow = **388 Ω**
* White ↔ Yellow = **383 Ω**
* Red ↔ semuanya = **OL**

**Ini sekarang masuk akal kalau kabel kuning yang kamu ukur bukan kabel asli load cell, melainkan titik gabungan resistor yang kamu buat.**

Artinya pengukuran sebelumnya jangan kita anggap sebagai karakteristik load cell 4-wire. Memang **load cell asli kamu adalah 3-wire**.

---

### Yang paling penting sekarang

Kalau resistor yang kamu maksud **400 kΩ**, **jangan lanjut dulu dengan resistor itu**.

Kalau contoh rangkaian yang kamu ikuti memang menggunakan **dua resistor 1 kΩ**, maka kita perlu tahu **resistor sebenarnya yang kamu pasang**.

Coba lihat tulisan/kode di badan resistor.

Misalnya:

```text
1000 Ω
1K
102
400K
404
```

Kalau kamu bilang "400k" karena multimeter membaca **400 kΩ**, berarti kemungkinan memang resistornya sekitar 400 kΩ.

**Foto resistor yang kamu pakai + rangkaian kabel load cell/HX711 kirim ke sini.** Dari foto itu saya bisa bantu gambar ulang **persis kabel mana → resistor mana → E+, E-, A+, A-**, supaya kita nggak salah konfigurasi lagi.
