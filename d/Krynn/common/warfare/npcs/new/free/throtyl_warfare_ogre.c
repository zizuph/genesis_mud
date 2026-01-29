
/* 
 * A Throtyl ogre of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/std_warfare_throtyl";

int level;
int sublevel = 3; // ogre

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0:
            level = 0; // 10% 'scarred' (112 stat average)
        break;
        case 1..5:
            level = 1; // 40% 'cunning' (125 stat average) 
        break;
        default:
            level = 2; // 50% 'brutal' (140 stat average)
        break;
    }

    return level;
}

public void
create_throtyl_soldier()
{
    set_throtyl_level(random_soldier_type(), sublevel, "throtyl");
}
 