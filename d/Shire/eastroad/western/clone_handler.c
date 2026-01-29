inherit "/d/Shire/std/clone_handler";

#include "../local.h"

string
random_animal()
{
    string *animals = get_dir(ANIMAL_DIR);
    string animal;

    animals = filter(animals, &wildmatch("*.c"));

    animal = animals[random(sizeof(animals))];
    return ANIMAL_DIR + animal[..-3];
}

void
create_clone_handler()
{
    set_default_area("/d/Shire/eastroad/western/");
    add_clone(random_animal, 1, 30);
}
