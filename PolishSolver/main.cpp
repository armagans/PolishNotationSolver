/*

Eğer ödevi istendiği gibi yaptıysanız bu kodu çalıştırdığınızda aşağıdaki çıktıyı almanız gerekiyor.
Eğer bu satırlar dışında çıktılar alıyorsanız ilgili hata mesajını inceleyip kodunuzu düzeltin.
Yanlış ifade örneklerini koda yazmadım. ıfadelerdeki yanlışlık parantezlerde, operatörlerde veya sayılarda olabilir.
Bu yorum kısmında birkaç örnek vereceğim:

Malformed expression örnekleri:
(+ 1 2
(*  3)
/ 100 (* 1 1))
(- 3 ( 4 ))

Kodun çıktısı:

(+ 1 2) = 3
(/ 1 4) = 0.25
(- (+ 1 2) 1 ) = 2
(/ (* 5 4) (+ (- 9 0) 1)) = 2
(+ (* 3 3) (* 4 4)) = 25
(* (- (+ 0 0) (/ 5 10) ) 10 ) = -5
(+ (* 3 3) (* 4 4)) = 25
(+ (- 0.25 (* 0.5 0.5)) 100.5) = 100.5
Tebrikler. En azindan ustteki ifadeler icin kodunuz dogru olarak calisiyor.

*/

#include "MathematicalExpression.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int main()
{

    /*
    Kontrol edilecek değerler:

    (+ 1 2) = 3.00

    (/ 1 4) = 0.25

    (- (+ 1 2) 1 ) = 2.00

    (+ (* 3 3) (* 4 4)) = 25.00

    (/ (* 5 4) (+ (- 9 0) 1)) = 2.00

    (* (- (+ 0 0) (/ 5 10) ) 10 ) = -5.00

    (+ (- 0.25 (* 0.5 0.5)) 100.5) = 100.5
    */
    double sonuc = 0;
    string str = "";
    int hataSayisi = 0;

    str = "(+ 1 2)";
    MathematicalExpression mexpr (str);
    sonuc = mexpr.evaluate();

    if(mexpr.getResult() != sonuc)
    {
        hataSayisi++;
        cout << "Hata: Evaluate edilmis deger, objenin degiskenine atilmamis." << endl;
    }

    str = "(/ 1 4)";
    mexpr.evaluate(str);

    str = "(- (+ 1 2) 1 )";
    mexpr.evaluate(str);

    str = "(/ (* 5 4) (+ (- 9 0) 1))";
    mexpr.evaluate(str);

    str = "(+ (* 3 3) (* 4 4))";
    mexpr.setExpression(str);
    if((sonuc = mexpr.evaluate()) != 25)
    {
        hataSayisi++;
        cout << "Hata: " << str << " degeri dogru hesaplanmadi. Hesaplanan deger = " << sonuc  <<endl;
    }

    str = "(* (- (+ 0 0) (/ 5 10) ) 10 )";
    sonuc = mexpr.evaluate(str);

    if(sonuc != -5)
    {
        hataSayisi++;
        cout << "Hata: " << str << " degeri dogru hesaplanmadi. Hesaplanan deger = " << sonuc  <<endl;
    }

    str = "(+ (* 3 3) (* 4 4))";
    // Burada 25 donmeli cunku en son (+ (* 3 3) (* 4 4)) expression'i set edilmisti.
    if((sonuc = mexpr.evaluate()) != 25)
    {
        hataSayisi++;
        cout << "Hata: " << str << " degeri dogru hesaplanmadi. Hesaplanan deger = " << sonuc  <<endl;
    }

    str = "(+ (- 0.25 (* 0.5 0.5)) 100.5)";
    mexpr.setExpression(str);

    if(mexpr.getResult() != 0)
    {
        hataSayisi++;
        cout << "Hata: setExpression  yapildigi halde result sifirlanmadi. Result = " << mexpr.getResult()  <<endl;
    }

    if((sonuc = mexpr.evaluate()) != 100.5)
    {
        hataSayisi++;
        cout << "Hata: " << str << " degeri dogru hesaplanmadi. Hesaplanan deger = " << sonuc  <<endl;
    }

    if(hataSayisi == 0)
    {
        cout << "Tebrikler. En azindan ustteki ifadeler icin kodunuz dogru olarak calisiyor." << endl;
    }
    else
    {
        cout << "Yapacak isiniz var. Ustteki ifadeler icin " << hataSayisi << " tane hataniz bulunmakta." << endl;
    }


    cout << endl << endl << "Hata mesaji durumlari asagidadir:" << endl;

    string hataDenemeleri[] = {  "(+ 2 3)",
                                 "(* (+ 2 3) 3)",
                                 "* (+ 2 3) 3)",
                                 "(* (+ 2.a 3) 3)",
                                 "(* (+ 2 3.a) 3)",
                                 "(* (+ 2 3..) 3)",
                                 "(* (+ 2 3) 3",
                                 "(* (+ 2 ) 3)",
                                 "(* (+ 2 3) )",
                                 "(* ( 2 3) 3)",
                                 "( ( 2 3) 3)",
                                 "(*( 2 3) 3)",
                                 "(* ( 2 3) 3)",
                                 "(* (+ 23) 3)",
                                 "(* (+ 2 3)3)",
                                 ""
                              };

    for(int i = 0; !hataDenemeleri[i].empty(); i++)
    {
        cout << i << ". expression = " << hataDenemeleri[i] << endl
             << "Hata mesaji = " << mexpr.expressionErrorMessage(hataDenemeleri[i]) << endl << endl;
    }

    return 0;
}
