#include <iostream>
#include "queue_vaksinasi.h"

void createQueue(Queue &Q) {
    head(Q) = NULL;
    tail(Q) = NULL;
}

bool isEmpty(Queue Q) {
    return head(Q) == NULL;
}

Address createElemQueue(string nama, int usia, string pekerjaan, int nomor_antrean) {
    Address P = new ElemQ;
    info(P).nama = nama;
    info(P).usia = usia;
    info(P).pekerjaan = pekerjaan;
    info(P).prioritas = (usia >= 60 || pekerjaan == "tenaga kesehatan");
    info(P).nomor_antrean = nomor_antrean;
    info(P).kondisi_darurat = false;
    info(P).waktu_daftar = 0;
    next(P) = NULL;
    return P;
}


void enqueue(Queue &Q, Address P) {
    if (isEmpty(Q)) {
        head(Q) = P;
        tail(Q) = P;
    } else if (info(P).prioritas) {
        if (!info(head(Q)).prioritas) {
            next(P) = head(Q);
            head(Q) = P;
        } else {
            Address temp = head(Q);
            while (next(temp) != NULL && info(next(temp)).prioritas) {
                temp = next(temp);
            }
            next(P) = next(temp);
            next(temp) = P;
            if (next(P) == NULL) {
                tail(Q) = P;
            }
        }
    } else {
        next(tail(Q)) = P;
        tail(Q) = P;
    }
}


void Dequeue(Queue& Q, Address& P) {
    if (isEmpty(Q)) {
        P = NULL;
        cout << "Semua warga telah terlayani." << endl;
    } else {
        P = head(Q);
        head(Q) = next(head(Q));
        if (head(Q) == NULL) {
            tail(Q) = NULL;
        }
        next(P) = NULL;
    }
}
Address front(Queue Q) {
    return head(Q);
}

Address back(Queue Q) {
    return tail(Q);
}

int size(Queue Q) {
    int count = 0;
    Address temp = head(Q);
    while (temp != NULL) {
        count++;
        temp = next(temp);
    }
    return count;
}

void printInfo(const Queue& Q) {
    if (isEmpty(Q)) {
        cout << "Antrean kosong." << endl;
    } else {
        cout << "Daftar Antrean:" << endl;
        Address temp = head(Q);
        while (temp != NULL) {
            cout << "Nama: " << info(temp).nama << endl;
            cout << "Usia: " << info(temp).usia << endl;
            cout << "Pekerjaan: " << info(temp).pekerjaan << endl;
            cout << "Prioritas: " << (info(temp).prioritas ? "Ya" : "Tidak") << endl;
            cout << "Nomor Antrean: " << info(temp).nomor_antrean << endl;
            cout << "=============================" << endl;
            temp = next(temp);
        }
    }
}


void serveQueue(Queue& Q) {
    const int maxCapacity = 100;
    int servedCount = 0;
    Address P;

    cout << "Melakukan pelayanan pada antrean:" << endl;

    while (!isEmpty(Q) && servedCount < maxCapacity) {
        Dequeue(Q, P);
        if (P != NULL) {
            cout << "Melayani warga:" << endl;
            cout << "Nama     : " << info(P).nama << endl;
            cout << "Usia     : " << info(P).usia << endl;
            cout << "Pekerjaan: " << info(P).pekerjaan << endl;
            cout << "Prioritas: " << (info(P).prioritas ? "Ya" : "Tidak") << endl;
            cout << "Vaksinasi berhasil." << endl;
            cout << "--------------------------------" << endl;
            servedCount++;
            delete P;
        }
    }

    if (servedCount == maxCapacity) {
        cout << "Kapasitas vaksinasi harian telah penuh (100 orang)." << endl;
    }

    int remaining = size(Q);
    if (remaining > 0) {
        cout << "Warga yang belum terlayani diminta kembali besok. Tersisa " << remaining << " warga dalam antrean." << endl;
    } else {
        cout << "Semua warga dalam antrean hari ini telah terlayani." << endl;
    }
}

void reassignQueue(Queue& Q) {
    Queue newQueue;
    createQueue(newQueue);
    Address P;

    while (!isEmpty(Q)) {
        Dequeue(Q, P);
        if (P != NULL) {
            if (info(P).prioritas) {
                enqueue(newQueue, P);
            } else {
                enqueue(newQueue, P);
            }
        }
    }

    Q = newQueue;
}

void checkWaitingTime(Queue& Q, int waktu_sekarang) {
    Queue updatedQueue;
    createQueue(updatedQueue);
    Address P;

    while (!isEmpty(Q)) {
        Dequeue(Q, P);
        if (P != NULL) {
            int waktu_tunggu = waktu_sekarang - info(P).waktu_daftar;
            cout << waktu_tunggu << endl;
            if (waktu_tunggu > 120 && !info(P).prioritas) {
                info(P).prioritas = true;
                info(P).kondisi_darurat = true;
            }
            enqueue(updatedQueue, P);
        }
    }

    Q = updatedQueue;
}

void emergencyHandle(Queue& Q, int nomor_antrean) {
    Queue updatedQueue;
    createQueue(updatedQueue);
    Address P;
    bool found = false;

    while (!isEmpty(Q)) {
        Dequeue(Q, P);
        if (P != NULL) {
            if (info(P).nomor_antrean == nomor_antrean) {
                info(P).kondisi_darurat = true;
                info(P).prioritas = true;
                found = true;
                enqueue(updatedQueue, P);
            } else {
                enqueue(updatedQueue, P);
            }
        }
    }

    Q = updatedQueue;

    if (!found) {
        cout << "Warga dengan nomor antrean " << nomor_antrean << " tidak ada dalam antrean." << endl;
    }
}

void updatePriority(Queue& Q) {
    Queue updatedQueue;
    createQueue(updatedQueue);
    Address P;

    while (!isEmpty(Q)) {
        Dequeue(Q, P);
        if (P != NULL) {
            int waktu_tunggu = 120;
            if (info(P).kondisi_darurat) {
                enqueue(updatedQueue, P);
            } else if (info(P).prioritas|| waktu_tunggu > 120) {
                enqueue(updatedQueue, P);
            } else {
                enqueue(updatedQueue, P);
            }
        }
    }

    Q = updatedQueue;
}

Address findAndRemove(Queue& Q, int nomor_antrean) {
    Queue tempQueue;
    createQueue(tempQueue);
    Address found = NULL;
    Address P;

    while (!isEmpty(Q)) {
        Dequeue(Q, P);
        if (P != NULL && info(P).nomor_antrean == nomor_antrean) {
            found = P;
            break;
        } else {
            enqueue(tempQueue, P);
        }
    }

    while (!isEmpty(Q)) {
        Dequeue(Q, P);
        enqueue(tempQueue, P);
    }

    if (found == NULL) {
        cout << "Warga dengan nomor antrean " << nomor_antrean << " tidak ada dalam antrean." << endl;
    }

    Q = tempQueue;
    return found;
}
