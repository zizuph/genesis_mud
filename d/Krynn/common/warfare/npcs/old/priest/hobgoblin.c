inherit "/d/Krynn/solamn/splains/living/hobgoblin";

void
create_krynn_monster()
{
    ::create_krynn_monster();
    string color = one_of_list(({"blue", "red", "black", "green", "white"}));
    set_color(color);
}

