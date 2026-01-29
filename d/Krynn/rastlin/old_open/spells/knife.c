inherit "/std/weapon";

create_weapon()
{
    set_name("knife");
    set_adj("short");
    set_short("short knife");
    set_long("A test knife, used by the magic system.\n");
}

int
test()
{
     string testt;

     testt = "kljhlk";

     return stringp(testt);
   }

