
/* 
 * A Seeker guard of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/std_warfare_seeker";

int level;
int sublevel = 1; // guard

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..3:
            level = 0; // 40% 'fervent' (112 stat average)
        break;
        case 4..6:
            level = 1; // 30% 'zealous' (125 stat average) 
        break;
        default:
            level = 2; // 30% 'veteran' (140 stat average)
        break;
    }

    return level;
}

public void
create_seeker_soldier()
{
    set_seeker_level(random_soldier_type(), sublevel, "seeker");
}
 