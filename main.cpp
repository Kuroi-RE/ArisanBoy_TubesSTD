// ARISAN BOY 1.0
#include <iostream>


void insertAnggota(AnggotaNode*& head, string nama, string alamat) {
    AnggotaNode* newAnggota = createAnggota(nama, alamat);
    if (!head) {
        head = newAnggota;
    } else {
        AnggotaNode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newAnggota;
    }
    cout << "Anggota '" << nama << "' berhasil ditambahkan.\n";
}

// Fungsi untuk menambahkan iuran anggota
void tambahIuran(AnggotaNode*& head) {
    string nama;

    cout << "Masukkan nama anggota: ";
    cin.ignore();
    getline(cin, nama);

    // Cek apakah nama anggota ada
    AnggotaNode* temp = head;
    while (temp) {
        if (temp->nama == nama) {
            if (temp->sudahIuran) {
                cout << "Anggota '" << nama << "' sudah melakukan iuran.\n";
                return; // Kembali ke menu utama
            }

            // Input jumlah iuran dengan error handling
            double jumlah;
            cout << "Masukkan jumlah iuran: ";
            while (true) {
                cin >> jumlah;
                if (cin.fail() || jumlah <= 0) {
                    cin.clear(); // Menghapus flag kesalahan
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang tidak valid
                    cout << "Input tidak valid. Harap masukkan jumlah iuran yang lebih dari 0: ";
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan sisa input
                    break; // Keluar dari loop jika input valid
                }
            }

            // Set iuran dan tandai anggota sudah melakukan iuran
            temp->jumlahIuran = jumlah;
            temp->sudahIuran = true;
            cout << "Iuran berhasil ditambahkan untuk '" << nama << "' dengan jumlah " << temp->jumlahIuran << ".\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Nama anggota '" << nama << "' tidak ditemukan dalam daftar.\n";
}


// Fungsi utama
int main() {
    AnggotaNode* head = nullptr;
    int pilihan;
    do {
        cout << "\nSistem Arisan Uang\n";
        cout << "1. Tambah Anggota\n";
        cout << "2. Tambah Iuran\n";
        cout << "3. Lihat Data\n";
        cout << "4. Pilih Pemenang\n";
        cout << "5. Cari Anggota\n";
        cout << "6. Hapus Anggota\n"; // Opsi baru untuk menghapus anggota
        cout << "7. Keluar\n";
        cout << "Pilih menu: ";
        pilihan = getInputInteger(); // Menggunakan fungsi untuk mendapatkan input integer

        if (pilihan == 1) {
            string nama, alamat;
            cout << "Masukkan nama: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Masukkan alamat: ";
            getline(cin, alamat);
            insertAnggota(head, nama, alamat);
        } else if (pilihan == 2) {
            tambahIuran(head);
        } else if (pilihan == 3) {
            viewData(head);
        } else if (pilihan == 4) {
            pilihPemenang(head);
        } else if (pilihan == 5) {
            findAnggota(head); // Memanggil fungsi findAnggota
        } else if (pilihan == 6) {
            deleteAnggota(head); // Memanggil fungsi deleteAnggota
        } else if (pilihan == 7) {
            cout << "Terima kasih telah menggunakan sistem arisan.\n";
        } else {
            cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 7);

    // Bebaskan memori sebelum keluar
    return 0;
}

