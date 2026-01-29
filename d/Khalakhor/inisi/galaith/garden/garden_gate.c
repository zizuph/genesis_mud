inherit "/d/Khalakhor/std/door";

void
create_khalakhor_door()
{
    set_name("gate");
    set_adj(({ "small", "black", "iron" }));
    set_long("A small, black-painted, iron gate stands at the entrance "+
       "to the garden.\n");

    set_open(0);
}
