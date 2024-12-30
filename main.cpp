// ARISAN BOY 1.0.1
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime> 
#include <limits> 
using namespace std;


struct AnggotaNode {
    string nama;
    string alamat;
    double jumlahIuran; 
    bool sudahIuran;
    AnggotaNode* next;
};


AnggotaNode* createAnggota(string nama, string alamat) {
    AnggotaNode* newAnggota = new AnggotaNode;
    newAnggota->nama = nama;
    newAnggota->alamat = alamat;
    newAnggota->jumlahIuran = 0.0; 
    newAnggota->sudahIuran = false; 
    newAnggota->next = nullptr;
    return newAnggota;
}

int countAnggota(AnggotaNode* head) {
    int count = 0;
    AnggotaNode* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}


void pilihPemenang(AnggotaNode*& head) {
    int totalAnggota = countAnggota(head);
    if (totalAnggota == 0) {
        cout << "Tidak ada anggota dalam sistem, tidak bisa memilih pemenang.\n";
        return;
    }

    AnggotaNode* temp = head;
    while (temp) {
        if (!temp->sudahIuran) {
            cout << "Semua anggota diharuskan memberikan iuran, tidak dapat memilih pemenang.\n";
            return;
        }
        temp = temp->next;
    }

    srand(time(0));
    int pemenangIndex = rand() % totalAnggota;
    temp = head;
    AnggotaNode* prev = nullptr;

    for (int i = 0; i < pemenangIndex; i++) {
        prev = temp;
        temp = temp->next;
    }

    cout << "Pemenang arisan adalah: " << temp->nama << " (" << temp->alamat << ")\n";

    if (prev) {
        prev->next = temp->next;
    } else {
        head = temp->next;
    }
    delete temp;
}


void viewData(AnggotaNode* head) {
    if (!head) {
        cout << "Tidak ada anggota dalam sistem.\n";
        return;
    }
    AnggotaNode* temp = head;
    while (temp) {
        cout << "Nama: " << temp->nama << "\nAlamat: " << temp->alamat << "\nIuran:\n";
        if (temp->sudahIuran) {
            cout << "  Jumlah: " << temp->jumlahIuran << "\n";
        } else {
            cout << "  Belum ada iuran.\n";
        }
        cout << "-----------------------------\n";
        temp = temp->next;
    }
}



void findAnggota(AnggotaNode* head) {
    string nama;
    cout << "Masukkan nama anggota yang dicari: ";
    getline(cin, nama);

    AnggotaNode* temp = head;
    while (temp) {
        if (temp->nama == nama) {
            cout << "Nama: " << temp->nama << "\nAlamat: " << temp->alamat << "\nIuran:\n";
            if (temp->sudahIuran) {
                cout << "  Jumlah: " << temp->jumlahIuran << "\n";
            } else {
                cout << "  Belum ada iuran.\n";
            }
            return; 
        }
        temp = temp->next;
    }
    cout << "Anggota dengan nama '" << nama << "' tidak ditemukan.\n";
}

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


void tambahIuran(AnggotaNode*& head) {
    string nama;

    cout << "Masukkan nama anggota: ";
    getline(cin, nama);

    AnggotaNode* temp = head;
    while (temp) {
        if (temp->nama == nama) {
            if (temp->sudahIuran) {
                cout << "Anggota '" << nama << "' sudah melakukan iuran.\n";
                return; 
            }

            double jumlah;
            cout << "Masukkan jumlah iuran (harus 100000): ";
            while (true) {
                cin >> jumlah;
                if (cin.fail() || jumlah != 100000) {
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "Input tidak valid. Harap masukkan jumlah iuran yang tepat 100000: ";
                } else {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    break; 
                }
            }

            temp->jumlahIuran = jumlah;
            temp->sudahIuran = true;
            cout << "Iuran berhasil ditambahkan untuk '" << nama << "' dengan jumlah " << temp->jumlahIuran << ".\n";
            return;
        }
        temp = temp->next;
    }

    cout << "Nama anggota '" << nama << "' tidak ditemukan dalam daftar.\n";
}

void deleteAnggota(AnggotaNode*& head) {
    string nama;
    cout << "Masukkan nama anggota yang ingin dihapus: ";
    getline(cin, nama);

    AnggotaNode* temp = head;
    AnggotaNode* prev = nullptr;

    while (temp) {
        if (temp->nama == nama) {
            if (prev) {
                prev->next = temp->next; 
            } else {
                head = temp->next; 
            }
            delete temp; 
            cout << "Anggota '" << nama << "' berhasil dihapus.\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Anggota dengan nama '" << nama << "' tidak ditemukan.\n";
}


int getInputInteger() {
    int input;
    while (true) {
        cin >> input;
        if (cin.fail()) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Input tidak valid. Harap masukkan angka bulat: ";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            return input; 
        }
    }
}

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
        cout << "6. Hapus Anggota\n"; 
        cout << "7. Keluar\n";
        cout << "Pilih menu: ";
        pilihan = getInputInteger(); 

        if (pilihan == 1) {
            string nama, alamat;
            cout << "Masukkan nama: ";
            getline(cin, nama);
            bool validNama = true;
            for (char c : nama) {
            if (!isalpha(c) && c != ' ') {
                validNama = false;
                break;
            }
            }
            if (nama.empty() || !validNama) {
            cout << "Nama tidak boleh kosong dan hanya boleh mengandung huruf alphabet. Coba lagi.\n";
            continue;
            }
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
            findAnggota(head); 
        } else if (pilihan == 6) {
            deleteAnggota(head); 
        } else if (pilihan == 7) {
            cout << "Terima kasih telah menggunakan sistem arisan.\n";
        } else {
            cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (pilihan != 7);

    
    return 0;
}

