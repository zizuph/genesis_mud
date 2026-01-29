inherit "/std/food";
#include <stdproperties.h>

public string day_of_week = (ctime(time())[0..2]);


/*
 * Function name: create_food()
 * Description  : Constructor.  Creates the food.
 */
create_food()
{
    determine_food();
}



/*
 * Function name: determine_food()
 * Description  : Constructor.  Creates the food based on day.
 */
int
determine_food()
{
    switch(day_of_week)
    {
        case "Sun":
            set_name("platter");
            set_adj("surf and turf");
            set_short("surf and turf platter");
            set_pshort("surf and turf platters");
            set_long("This is a collection of fish fillets and slices of "
            +"some sort of gravy-covered mystery meat. The fish at "
            +"least looks edible.\n");
            set_amount(320);
            break;
        case "Mon":
            set_name("liver and onions");
            set_adj("cod");
            set_short("cod liver and onions");
            set_pshort("cod liver and onions");
            set_long("It used to be hard to imagine anything worse than "
            +"liver and onions; then you encountered this meal. An odd "
            +"take on an old idea, "
            +"the locals swear by this dish.\n");
            set_amount(320);
            break;
        case "Tue":
            set_name("casserole");
            set_adj("tuna noodle");
            set_short("tuna noodle casserole");
            set_pshort("tuna noodle casseroles");
            set_long("This casserole is billed as a premier dish.  Though "
            +"it certainly wouldn't be a first "
            +"choice, it at least appears more palatable than other "
            +"meals from this place.\n");
            set_amount(320);
            break;
        case "Wed":
            set_name("fish and chips");
            set_adj("oily");
            set_short("oily fish and chips");
            set_pshort("oily fish and chips");
            set_long("This is a classic fish and chips. It actually "
            +"doesn't look half bad if you can "
            +"stomach the oil, which is falling quickly onto the ground "
            +"in front of you.\n");
            set_amount(320);
            break;
        case "Thu":
            set_name("haddock");
            set_adj("oven-baked");
            set_short("oven-baked haddock");
            set_pshort("oven-baked haddocks");
            set_long("This is an oven baked haddock. It appears "
            +"a bit overcooked and dry, but is at "
            +"least fully cooked and edible. It is plated with a "
            +"side of asparagus.\n");
            set_amount(320);
            break;
        case "Fri":
            set_name("calamari");
            set_adj("rubbery");
            set_short("rubbery calamari");
            set_pshort("rubbery calamaris");
            set_long("This is an order of calamari. The squid "
            +"is a tad on the overdone side, "
            +"and as such has gotten a bit rubbery. An dipping sauce is "
            +"included, though you are unsure what kind.\n");
            set_amount(320);
            break;
        case "Sat":
            set_name("patty");
            set_adj("crab");
            set_short("crab patty");
            set_pshort("crab patties");
            set_long("This is a medium sized crab patty. It is "
            +"surrounded by slightly stale bread and "
            +"has been lathered with mayonnaise. It appears to be an "
            +"adequate meal.\n");
            set_amount(320);
            break;
    }   
}