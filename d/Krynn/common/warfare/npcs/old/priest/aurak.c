inherit "/d/Krynn/std/aurak";

void
create_aurak()
{
    string color = one_of_list(({"blue", "red", "black", "green", "white"}));
    set_color(color);
}
