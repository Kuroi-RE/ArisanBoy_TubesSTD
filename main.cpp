// ARISAN BOY 1.0
#include <iostream>

int countAnggota(AnggotaNode* head) {
    int count = 0;
    AnggotaNode* temp = head;
    while (temp) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Fungsi untuk memilih pemenang secara acak
void pilihPemenang(AnggotaNode*& head) {
    int totalAnggota = countAnggota(head);
    if (totalAnggota == 0) {
        cout << "Tidak ada anggota dalam sistem, tidak bisa memilih pemenang.\n";
        return;
    }

    srand(time(0));
    int pemenangIndex = rand() % totalAnggota;

    AnggotaNode* temp = head;
    AnggotaNode* prev = nullptr;
    for (int i = 0; i < pemenangIndex; i++) {
        prev = temp;
        temp = temp->next;
    }

    cout << "Pemenang arisan adalah: " << temp->nama << " (" << temp->alamat << ")\n";

    // Hapus pemenang dari daftar anggota
    if (prev) {
        prev->next = temp->next; // Menghubungkan node sebelumnya ke node berikutnya
    } else {
        head = temp->next; // Jika pemenang adalah anggota pertama
    }
    delete temp; // Hapus node pemenang
}
