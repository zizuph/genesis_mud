inherit "/d/Krynn/std/bozak";

void
create_bozak()
{
    string color = one_of_list(({"blue", "red", "black", "green", "white"}));
    set_color(color);
}
