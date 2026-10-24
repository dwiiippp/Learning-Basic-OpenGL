# OpenGL Project Setup Guide (Meson + Ninja)

Panduan ini berisi langkah-langkah untuk melakukan setup, kompilasi, dan menjalankan proyek OpenGL menggunakan sistem build **Meson** dan **Ninja**.

## 📁 Struktur Proyek

```
.
├── .vscode/          # Konfigurasi Editor (VS Code)
├── include/          # Berkas Header (.h / .hpp)
├── libraries/        # Depedensi / Library eksternal (misal: GLFW, GLM)
├── resources/        # Asset proyek (Shader, Tekstur, Model, dll.)
├── src/              # Berkas Kode Sumber C/C++
│   ├── glad.c
│   ├── main.cpp
│   ├── ShaderManajer.cpp
│   └── ShaderManajer.h
├── meson.build       # Konfigurasi Sistem Build Meson
└── README.md

```

## 🛠️ Prasyarat (Prerequisites)

Sebelum memulai, pastikan perangkat Anda telah terpasang dependensi berikut:

1. **Kompiler C/C++**:

   * **Windows**: MSVC (Visual Studio) atau MinGW-w64 (GCC/G++)

   * **Linux**: GCC atau Clang

   * **macOS**: Clang / Xcode Command Line Tools

2. **Python 3**: Diperlukan untuk menjalankan Meson.

3. **Meson**: Sistem pembuatan build berkinerja tinggi.

4. **Ninja**: Backend pembangun otomatis berkecepatan tinggi.

5. **OpenGL Drivers**: Driver kartu grafis terpasang dengan benar.

## 📥 Instalasi Alat Build

### 1. Menginstall Meson & Ninja

Jalankan perintah berikut di terminal/command prompt:

```
pip install meson ninja

```

Atau menggunakan manager paket OS:

* **Ubuntu/Debian**:

  ```
  sudo apt update && sudo apt install meson ninja-build
  
  ```

* **Arch Linux**:

  ```
  sudo pacman -S meson ninja
  
  ```

* **macOS (Homebrew)**:

  ```
  brew install meson ninja
  
  ```

## 🚀 Langkah Setup & Kompilasi Project

### 1. Klon / Buka Direktori Project

Buka terminal dan masuk ke direktori utama proyek:

```
cd path/to/your/project

```

### 2. Inisialisasi Direktori Build (Meson Setup)

Jalankan Meson untuk mengonfigurasi proyek dan membuat direktori build (`builddir`):

```
meson setup builddir

```

> **Catatan:** Jika Anda ingin mengubah tipe build (misal ke `release` atau `debug`):
>
> ```
> meson setup builddir --buildtype=debug
> 
> ```

### 3. Kompilasi Proyek (Ninja Compile)

Jalankan kompilasi menggunakan Meson/Ninja:

```
meson compile -C builddir

```

Atau langsung menggunakan perintah Ninja:

```
ninja -C builddir

```

## 🏃 Cara Menjalankan Aplikasi

Setelah proses kompilasi selesai, file eksekusi (*executable*) akan berada di dalam folder `builddir`.

* **Windows**:

  ```
  .\builddir\main.exe
  
  ```

* **Linux / macOS**:

  ```
  ./builddir/main
  
  ```

## 🧹 Perintah Tambahan (Maintenance)

* **Membersihkan hasil kompilasi (Clean):**

  ```
  ninja -C builddir clean
  
  ```

* **Menghapus total folder build:**
  Jika Anda mengubah `meson.build` secara signifikan atau ingin mengulang dari awal:

  ```
  rm -rf builddir
  meson setup builddir
  
  ```

* **Reconfigure Meson:**

  ```
  meson setup --reconfigure builddir
  
  ```

## 💡 Troubleshooting Common Issues

1. **Library Not Found (GLFW / OpenGL / GLAD):**

   * Pastikan path perpustakaan pada `meson.build` sudah mengarah ke direktori `libraries/` dan `include/` dengan benar.

2. **Shader / Resource Not Loading:**

   * Pastikan aplikasi dijalankan dari root direktori proyek agar relatif path ke folder `resources/` dapat dibaca dengan tepat.