inherit "/d/Krynn/solamn/splains/living/goblin";

void
create_krynn_monster()
{
    ::create_krynn_monster();
    string color = one_of_list(({"blue", "red", "black", "green", "white"}));
    set_color(color);
}

