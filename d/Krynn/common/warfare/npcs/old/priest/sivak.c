inherit "/d/Krynn/std/sivak";

void
create_sivak()
{
    string color = one_of_list(({"blue", "red", "black", "green", "white"}));
    set_color(color);
}
