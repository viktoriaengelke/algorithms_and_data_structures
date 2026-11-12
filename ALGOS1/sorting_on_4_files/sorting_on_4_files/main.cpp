#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

void create_file(const string& file_name, int k)
{
    ofstream f(file_name.c_str());
    if (!f.is_open()) return;
    
    for (int i = 0; i < k; i++)
        f<<rand()%100<<" ";
    
    f.close();
}
void print_file(const string& file_name)
{
    ifstream f(file_name.c_str());
    if (!f.is_open()) return;
    
    int x;
    while (f >> x)
        cout<<x<<" ";
    f.close();
    cout<<endl;
}
int count_elements(const string& name)
{
    ifstream f(name.c_str());
    if (!f.is_open()) return 0;
    
    int x;
    int count = 0;
    while (f >> x)
    {
        count++;
    }
    f.close();
    
    return count;
}
void copy_file(const string& s, const string& d)
{
    ifstream in(s.c_str());
    ofstream out(d.c_str());
    
    if (! in.is_open() || !out.is_open()) return;
    
    int x;
    while (in >> x)
        out<<x<<" ";
    
    in.close();
    out.close();
}
void clear_file(const string& name)
{
    ofstream f;
    f.open(name.c_str(), ios::trunc);
    f.close();
}
void split(const string& f1, const string& fa1, const string& fb1)
{
    ifstream f(f1.c_str());
    ofstream fa(fa1.c_str());
    ofstream fb(fb1.c_str());
    
    if (!f.is_open() || !fa.is_open() || !fb.is_open()) return;
    
    int x, prev;
    int file_num = 0;
    
    if (!(f >> prev))
    {
        f.close();
        fa.close();
        fb.close();
        return;
    }
    
    fa << prev << " ";
    
    while (f >> x)
    {
        if (x < prev)
            file_num = 1 - file_num;
        
        if (file_num == 0)
            fa << x << " ";
        else
            fb << x << " ";
        
        prev = x;
    }
    
    f.close();
    fa.close();
    fb.close();
}
bool is_sorted(const string& name)
{
    ifstream f(name.c_str());
    if (!f.is_open()) return false;
    
    int prev, curr;
    if (!(f >> prev)) return true;
    
    while (f >> curr)
    {
        if (curr < prev) return false;
        prev = curr;
    }
    
    f.close();
    return true;
}

void merge(const string& fa1, const string& fb1, const string& fc1, const string& fd1)
{
    ifstream fa(fa1.c_str());
    ifstream fb(fb1.c_str());
    ofstream fc(fc1.c_str(), ios::trunc);
    ofstream fd(fd1.c_str(), ios::trunc);
    
    if (!fa.is_open() || !fb.is_open() || !fc.is_open() || !fd.is_open()) return;
    
    int a, b;
    int file_num = 0;
    
    if (!(fa >> a))
    {
        while (fb >> b) fc << b << " ";
        return;
    }
    if (!(fb >> b))
    {
        fc << a << " ";
        while (fa >> a) fc << a << " ";
        return;
    }
    
    int fa_ok = 1;
    int fb_ok = 1;
    
    while (fa_ok || fb_ok)
    {
        ofstream* out = (file_num == 0) ? &fc : &fd;
        int prev_a = a;
        int prev_b = b;
        
        while (fa_ok && fb_ok)
        {
            if (a <= b)
            {
                *out << a << " ";
                prev_a = a;
                if (!(fa >> a)) { fa_ok = 0; break; }
                if (a < prev_a) break;
            }
            else
            {
                *out << b << " ";
                prev_b = b;
                if (!(fb >> b)) { fb_ok = 0; break; }
                if (b < prev_b) break;
            }
        }
        
        while (fa_ok)
        {
            if (a < prev_a) break;
            *out << a << " ";
            prev_a = a;
            if (!(fa >> a)) { fa_ok = 0; break; }
        }
        
        while (fb_ok)
        {
            if (b < prev_b) break;
            *out << b << " ";
            prev_b = b;
            if (!(fb >> b)) { fb_ok = 0; break; }
        }
        
        file_num = 1 - file_num;
    }
    
    fa.close();
    fb.close();
    fc.close();
    fd.close();
}
void sort(const string& f, const string& fa, const string& fb,
          const string& fc, const string& fd)
{
    clear_file(fa);
    clear_file(fb);
    clear_file(fc);
    clear_file(fd);
    
    split(f, fa, fb);
    
    if (count_elements(fb) == 0)
        return;
    
    while (true)
    {
        clear_file(fc);
        clear_file(fd);
        merge(fa, fb, fc, fd);
        
        if (count_elements(fd) == 0)
            return;
        
        clear_file(fa);
        clear_file(fb);
        merge(fc, fd, fa, fb);
        
        if (count_elements(fb) == 0) return;
    }
}
//void sort(const string& f, const string& fa, const string& fb,
//          const string& fc, const string& fd)
//{
//    clear_file(fa);
//    clear_file(fb);
//    clear_file(fc);
//    clear_file(fd);
//    
//    split(f, fa, fb);
//    
//    cout << "После split: fa=" << count_elements(fa) << " fb=" << count_elements(fb) << endl;
//    
//    if (count_elements(fb) == 0)
//    {
//        cout << "fb пуст, файл уже отсортирован" << endl;
//        copy_file(f, fa);
//        return;
//    }
//    
//    int step = 0;
//    while (true)
//    {
//        step++;
//        
//        clear_file(fc);
//        clear_file(fd);
//        merge(fa, fb, fc, fd);
//        
//        int cnt_fc = count_elements(fc);
//        int cnt_fd = count_elements(fd);
//        
//        cout << "Шаг " << step << " (fa+fb->fc+fd): fc=" << cnt_fc << " fd=" << cnt_fd << endl;
//        
//        if (cnt_fd == 0)
//        {
//            cout << "fd пуст, результат в fc" << endl;
//            copy_file(fc, fa);
//            break;
//        }
//        
//        clear_file(fa);
//        clear_file(fb);
//        merge(fc, fd, fa, fb);
//        
//        int cnt_fa = count_elements(fa);
//        int cnt_fb = count_elements(fb);
//        
//        cout << "Шаг " << step << " (fc+fd->fa+fb): fa=" << cnt_fa << " fb=" << cnt_fb << endl;
//        
//        if (cnt_fb == 0)
//        {
//            cout << "fb пуст, результат в fa" << endl;
//            break;
//        }
//    }
//    
//    cout << "Сортировка завершена: fa=" << count_elements(fa) << " fc=" << count_elements(fc) << endl;
//}
int main() {
    srand(time(NULL));
    
    const string f = "f.txt";
    const string fa = "fa.txt";
    const string fb = "fb.txt";
    const string fc = "fc.txt";
    const string fd = "fd.txt";
    
    int k;
    cout << "enter number of elements: ";
    cin >> k;
    
    create_file(f, k);
    
    cout << "\noriginal file: ";
    print_file(f);
    
    sort(f, fa, fb, fc, fd);

    if (count_elements(fb) == 0)
    {
        cout << "sorted file (fa): ";
        print_file(fa);
        cout<<count_elements(fa)<<endl;
        cout<<is_sorted(fa)<<endl;
    }
    else if (count_elements(fd) == 0)
    {
        cout << "sorted file (fc): ";
        print_file(fc);
        cout<<count_elements(fc)<<endl;
        cout<<is_sorted(fc)<<endl;
    }
    return 0;
}
