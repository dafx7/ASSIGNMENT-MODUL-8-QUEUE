#ifndef QUEUE_VAKSINASI_H
#define QUEUE_VAKSINASI_H

#include <string>
#define info(P) (P)->info
#define next(P) (P)->next
#define head(S) ((S).head)
#define tail(S) ((S).tail)
using namespace std;

struct Infotype {
    string nama;
    int usia;
    string pekerjaan;
    bool prioritas;
    int nomor_antrean;
    int waktu_daftar; // waktu dalam menit
    bool kondisi_darurat;
};

struct ElemQ;

typedef ElemQ* Address;

struct ElemQ {
    Infotype info;
    Address next;
};

struct Queue {
    Address head;
    Address tail;
};

void createQueue_103012300198(Queue &Q);
bool isEmpty_103012300198_103012300198(Queue Q);
Address createElemQueue(string nama, int usia, string pekerjaan, int nomor_antrean);
void enqueue(Queue &Q, Address P);
void Dequeue(Queue& Q, Address& P);
Address front(Queue Q);
Address back(Queue Q);
int size(Queue Q);
void printInfo_103012300198(const Queue& Q);
void serveQueue(Queue& Q);
void reassignQueue(Queue& Q);
void checkWaitingTime(Queue& Q, int waktu_sekarang);
void emergencyHandle(Queue& Q, int nomor_antrean);
void updatePriority(Queue& Q);
Address findAndRemove(Queue& Q, int nomor_antrean);

#endif // QUEUE_VAKSINASI_H
