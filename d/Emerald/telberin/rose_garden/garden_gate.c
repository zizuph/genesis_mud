inherit "/d/Emerald/std/door";

void
create_emerald_door()
{
    set_name("gate");
    set_adj(({ "small", "bronze", }));
    set_long("A small, bronze gate which is covered in a glorious "+
      "emerald vine with stunning miniture red and white roses stands "+
      "at the entrance to the garden.\n");

    set_open(0);
}
