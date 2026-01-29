
/* 
 * A Throtyl hobgoblin of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/std_warfare_throtyl";

int level;
int sublevel = 1; // hobgoblin

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..3:
            level = 0; // 40% 'scarred' (112 stat average)
        break;
        case 4..6:
            level = 1; // 30% 'cunning' (125 stat average) 
        break;
        default:
            level = 2; // 30% 'brutal' (140 stat average)
        break;
    }

    return level;
}

public void
create_throtyl_soldier()
{
    set_throtyl_level(random_soldier_type(), sublevel, "throtyl");
}
 