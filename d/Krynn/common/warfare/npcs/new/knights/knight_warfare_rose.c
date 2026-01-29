
/* 
 * A knight of the Rose of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/knight_base";

int level;
int sublevel = 4; // Rose knight

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..1:
            level = 3; // 20% 'fearless' (139 stat average)
        break;
        case 2..6:
            level = 4; // 50% 'heroic' (169 stat average) 
        break;
        default:
            level = 5; // 30% 'elite' (189 stat average)
        break;
    }

    return level;
}

public void
create_knight_soldier()
{
    set_knight_level(random_soldier_type(), sublevel, "rose");
}
 