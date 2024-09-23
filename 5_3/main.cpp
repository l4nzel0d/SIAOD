#include "Hash_Table.h"

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");
    Hash_Table library(5);

    library.insert(64196, "Григорьев Егор Алексеевич", "ул. Ленина д. 115");
    library.insert(71178, "Иванов Михаил Вячеславович", "ул. Краснопресненская д. 35");
    library.insert(21339, "Смирнов Максим Никитич", "ул. Арбат д. 101");
    library.insert(88642, "Морозов Сергей Павлович", "ул. Тверская д. 72");
    library.insert(76992, "Орлов Михаил Юрьевич", "ул. Чехова д. 119");

    library.display();

}