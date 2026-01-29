
/* 
 * A Qualinesti elf archer of the warfare system.
 */

inherit "/d/Krynn/common/warfare/npcs/new/std/std_warfare_qualinesti";

int level;
int sublevel = 3; // archer

int
random_soldier_type()
{
    int rand = random(10);

    switch(rand)
    {
        case 0..4:
            level = 1; // 50% 'experienced' (125 stat average) 
        break;
        default:
            level = 2; // 50% 'veteran' (140 stat average)
        break;
    }

    return level;
}

public void
create_elf_soldier()
{
    set_elf_level(random_soldier_type(), sublevel, "qualinesti");
}
 