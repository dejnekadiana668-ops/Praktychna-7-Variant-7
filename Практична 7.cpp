#include <iostream>
using namespace std;

const int MAX = 1000;

// Лічильники операцій
struct Stat {
    int por = 0;
    int zap = 0;
};

// Виведення масиву
void pokazaty(const int a[], int n) {
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}

// Копіювання масиву
void kopiya(const int a[], int b[], int n) {
    for (int i = 0; i < n; i++)
        b[i] = a[i];
}

// Обмін елементів
void obmin(int& a, int& b, Stat& s) {
    int t = a;
    a = b;
    b = t;
    s.zap += 3;
}

// Перевірка сортування
bool pravilno(const int a[], int n) {
    for (int i = 1; i < n; i++)
        if (a[i - 1] > a[i])
            return false;
    return true;
}

// Перевірка збереження чисел
bool sklad(const int a[], const int b[], int n) {
    for (int i = 0; i < n; i++) {
        int x = 0, y = 0;

        for (int j = 0; j < n; j++) {
            if (a[j] == a[i]) x++;
            if (b[j] == a[i]) y++;
        }
        if (x != y) return false;
    }

    for (int i = 0; i < n; i++) {
        int x = 0, y = 0;

        for (int j = 0; j < n; j++) {
            if (a[j] == b[i]) x++;
            if (b[j] == b[i]) y++;
        }
        if (x != y) return false;
    }
    return true;
}

// Завдання 1. Злиття двох частин
void zlyttya(int a[], int l, int m, int r,
    Stat& s, bool trasa = false) {
    int b[MAX] = {};
    int i = l, j = m + 1, k = l;

    while (i <= m && j <= r) {
        s.por++;

        if (a[i] <= a[j])
            b[k++] = a[i++];
        else
            b[k++] = a[j++];

        s.zap++;
    }

    while (i <= m) {
        b[k++] = a[i++];
        s.zap++;
    }

    while (j <= r) {
        b[k++] = a[j++];
        s.zap++;
    }

    for (int x = l; x <= r; x++) {
        a[x] = b[x];
        s.zap++;
    }

    if (trasa) {
        cout << "Злиття [" << l << ".." << r << "]: ";
        for (int x = l; x <= r; x++)
            cout << a[x] << " ";
        cout << endl;
    }
}

// Завдання 3. Рекурсивний поділ
void mergeSort(int a[], int l, int r,
    Stat& s, bool trasa = false) {
    if (l >= r) return;

    int m = (l + r) / 2;

    if (trasa)
        cout << "Поділ [" << l << ".." << r
        << "] на [" << l << ".." << m
        << "] і [" << m + 1 << ".." << r << "]\n";

    mergeSort(a, l, m, s, trasa);
    mergeSort(a, m + 1, r, s, trasa);
    zlyttya(a, l, m, r, s, trasa);
}

// Завдання 2. Тестування злиття
void testZlyttya(const int a[], int n, int m, int nomer) {
    int b[MAX] = {};
    kopiya(a, b, n);

    Stat s;
    zlyttya(b, 0, m, n - 1, s);

    cout << "Тест " << nomer << ": "
        << (pravilno(b, n) && sklad(a, b, n)
            ? "успішно" : "помилка")
        << endl;
}

// Завдання 7. Тестування MergeSort
void testMerge(const int a[], int n, int nomer) {
    int b[MAX] = {};
    kopiya(a, b, n);

    Stat s;
    if (n > 0)
        mergeSort(b, 0, n - 1, s);

    cout << "Тест " << nomer << ": "
        << (pravilno(b, n) && sklad(a, b, n)
            ? "успішно" : "помилка")
        << endl;
}

// Завдання 8. Інші алгоритми сортування

void insertion(int a[], int n, Stat& s) {
    for (int i = 1; i < n; i++) {
        int x = a[i], j = i - 1;
        while (j >= 0) {
            s.por++;
            if (a[j] <= x) break;
            a[j + 1] = a[j];
            s.zap++;
            j--;
        }
        a[j + 1] = x;
        s.zap++;
    }
}

void selection(int a[], int n, Stat& s) {
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            s.por++;
            if (a[j] < a[k]) k = j;
        }
        if (k != i) obmin(a[i], a[k], s);
    }
}

void bubble(int a[], int n, Stat& s) {
    for (int i = 0; i < n - 1; i++) {
        bool zmina = false;
        for (int j = 0; j < n - i - 1; j++) {
            s.por++;
            if (a[j] > a[j + 1]) {
                obmin(a[j], a[j + 1], s);
                zmina = true;
            }
        }
        if (!zmina) break;
    }
}

void binaryInsertion(int a[], int n, Stat& s) {
    for (int i = 1; i < n; i++) {
        int x = a[i], l = 0, r = i;
        while (l < r) {
            int m = (l + r) / 2;
            s.por++;
            if (a[m] <= x) l = m + 1;
            else r = m;
        }
        for (int j = i; j > l; j--) {
            a[j] = a[j - 1];
            s.zap++;
        }
        a[l] = x;
        s.zap++;
    }
}

void shaker(int a[], int n, Stat& s) {
    int l = 0, r = n - 1;
    while (l < r) {
        bool zmina = false;
        for (int i = l; i < r; i++) {
            s.por++;
            if (a[i] > a[i + 1]) {
                obmin(a[i], a[i + 1], s);
                zmina = true;
            }
        }
        r--;
        if (!zmina) break;

        zmina = false;
        for (int i = r; i > l; i--) {
            s.por++;
            if (a[i - 1] > a[i]) {
                obmin(a[i - 1], a[i], s);
                zmina = true;
            }
        }
        l++;
        if (!zmina) break;
    }
}

void shell(int a[], int n, Stat& s) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int x = a[i], j = i;
            while (j >= gap) {
                s.por++;
                if (a[j - gap] <= x) break;
                a[j] = a[j - gap];
                s.zap++;
                j -= gap;
            }
            a[j] = x;
            s.zap++;
        }
    }
}

void quick(int a[], int l, int r, Stat& s) {
    if (l >= r) return;

    int x = a[r], i = l;
    for (int j = l; j < r; j++) {
        s.por++;
        if (a[j] < x) {
            if (i != j) obmin(a[i], a[j], s);
            i++;
        }
    }
    if (i != r) obmin(a[i], a[r], s);

    quick(a, l, i - 1, s);
    quick(a, i + 1, r, s);
}

void heapify(int a[], int n, int i, Stat& s) {
    while (true) {
        int k = i;
        int l = 2 * i + 1, r = 2 * i + 2;

        if (l < n) {
            s.por++;
            if (a[l] > a[k]) k = l;
        }
        if (r < n) {
            s.por++;
            if (a[r] > a[k]) k = r;
        }
        if (k == i) break;

        obmin(a[i], a[k], s);
        i = k;
    }
}

void heap(int a[], int n, Stat& s) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i, s);

    for (int i = n - 1; i > 0; i--) {
        obmin(a[0], a[i], s);
        heapify(a, i, 0, s);
    }
}

// Завдання 8. Порівняння алгоритмів
void porivnyannya(const int a[], int n) {
    const char* nazvy[] = {
        "Вставки", "Вибір", "Бульбашка",
        "Бінарні вставки", "Шейкер",
        "Шелл", "QuickSort", "HeapSort", "MergeSort"
    };

    cout << "Алгоритм | Порівняння | Записи | Перевірка\n";

    for (int t = 0; t < 9; t++) {
        int b[MAX] = {};
        kopiya(a, b, n);
        Stat s;

        switch (t) {
        case 0: insertion(b, n, s); break;
        case 1: selection(b, n, s); break;
        case 2: bubble(b, n, s); break;
        case 3: binaryInsertion(b, n, s); break;
        case 4: shaker(b, n, s); break;
        case 5: shell(b, n, s); break;
        case 6: quick(b, 0, n - 1, s); break;
        case 7: heap(b, n, s); break;
        case 8: mergeSort(b, 0, n - 1, s); break;
        }

        cout << nazvy[t] << " | "
            << s.por << " | " << s.zap << " | "
            << (pravilno(b, n) && sklad(a, b, n)
                ? "успішно" : "помилка")
            << endl;
    }
}

int main() {
    const int n = 16;
    int a[n] = {
        20, 32, 7, 25, 11, 3, 28, 14,
        1, 22, 9, 30, 5, 17, 12, 27
    };

    // ==================================
    // ЗАВДАННЯ 1. ЗЛИТТЯ ДВОХ ЧАСТИН
    // ==================================

    cout << "\nЗавдання 1. Злиття двох частин\n";

    int z[] = { 1, 5, 9, 2, 4, 8 };
    cout << "До злиття: ";
    pokazaty(z, 6);

    Stat s1;
    zlyttya(z, 0, 2, 5, s1);

    cout << "Після злиття: ";
    pokazaty(z, 6);

    // ==================================
    // ЗАВДАННЯ 2. ТЕСТИ ЗЛИТТЯ
    // ==================================

    cout << "\nЗавдання 2. Тести злиття\n";

    int z1[] = { 1, 3, 2, 4 };
    int z2[] = { 1, 2, 3, 4 };
    int z3[] = { 2, 4, 1, 3 };
    int z4[] = { -5, 0, -3, 2 };
    int z5[] = { 1, 1, 1, 1 };

    testZlyttya(z1, 4, 1, 1);
    testZlyttya(z2, 4, 1, 2);
    testZlyttya(z3, 4, 1, 3);
    testZlyttya(z4, 4, 1, 4);
    testZlyttya(z5, 4, 1, 5);

    // ==================================
    // ЗАВДАННЯ 3. РЕКУРСИВНИЙ ПОДІЛ
    // ==================================

    cout << "\nЗавдання 3. Рекурсивний поділ\n";

    cout << "Поділ масиву виконується навпіл.\n";

    // ==================================
    // ЗАВДАННЯ 4. ТРАСУВАННЯ
    // ==================================

    cout << "\nЗавдання 4. Трасування поділу і злиття\n";

    int b[n] = {};
    kopiya(a, b, n);

    Stat s;
    mergeSort(b, 0, n - 1, s, true);

    // ==================================
    // ЗАВДАННЯ 5. СТАТИСТИКА
    // ==================================

    cout << "\nЗавдання 5. Статистика\n";

    cout << "Порівняння: " << s.por << endl;
    cout << "Записи: " << s.zap << endl;
    cout << "Усього операцій: " << s.por + s.zap << endl;

    // ==================================
    // ЗАВДАННЯ 6. АВТОМАТИЧНА ПЕРЕВІРКА
    // ==================================

    cout << "\nЗавдання 6. Автоматична перевірка\n";

    cout << "Порядок: "
        << (pravilno(b, n) ? "правильний" : "помилка")
        << endl;

    cout << "Склад: "
        << (sklad(a, b, n) ? "збережено" : "помилка")
        << endl;

    cout << "Відсортований масив: ";
    pokazaty(b, n);

    // ==================================
    // ЗАВДАННЯ 7. ТЕСТИ MERGESORT
    // ==================================

    cout << "\nЗавдання 7. Тести MergeSort\n";

    int t1[] = { 5 };
    int t2[] = { 2, 1 };
    int t3[] = { 1, 2, 3, 4, 5 };
    int t4[] = { 5, 4, 3, 2, 1 };
    int t5[] = { 3, 3, 3, 3 };
    int t6[] = { 4, 1, 4, 2, 1 };
    int t7[] = { -3, 0, 5, -1, 2 };
    int t8[] = { 10, 7, 8, 9, 1, 5 };
    int t9[] = { 0, -1, 0, -1, 0 };
    int t10[] = { 8, 8, 2, 9, 2, 1 };

    testMerge(a, n, 1);
    testMerge(t1, 1, 2);
    testMerge(t2, 2, 3);
    testMerge(t3, 5, 4);
    testMerge(t4, 5, 5);
    testMerge(t5, 4, 6);
    testMerge(t6, 5, 7);
    testMerge(t7, 5, 8);
    testMerge(t8, 6, 9);
    testMerge(t9, 5, 10);
    testMerge(t10, 6, 11);
    testMerge(a, 0, 12);

    // ==================================
    // ЗАВДАННЯ 8. ПОРІВНЯННЯ
    // ==================================

    cout << "\nЗавдання 8. Порівняння алгоритмів\n";

    porivnyannya(a, n);

    return 0;
}