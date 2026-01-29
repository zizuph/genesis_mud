inherit "/d/Krynn/std/baaz";

void
create_baaz()
{
    string color = one_of_list(({"blue", "red", "black", "green", "white"}));
    set_color(color);
}
