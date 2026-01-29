
/* 
 * A Seeker believer of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/std_warfare_seeker";

int level;
int sublevel = 0; // believer

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..4:
            level = 0; // 50% 'fervent' (112 stat average)
        break;
        case 5..7:
            level = 1; // 30% 'zealous' (125 stat average) 
        break;
        default:
            level = 2; // 20% 'veteran' (140 stat average)
        break;
    }

    return level;
}

public void
create_seeker_soldier()
{
    set_seeker_level(random_soldier_type(), sublevel, "seeker");
}
 