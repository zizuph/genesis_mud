inherit "/d/Krynn/std/kapak";

void
create_kapak()
{
    string color = one_of_list(({"blue", "red", "black", "green", "white"}));
    set_color(color);
}
