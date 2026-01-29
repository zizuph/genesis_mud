#include <formulas.h>

/*
 * Function name:   make_scar
 * Description:     Add a random scar to a person.
 */
static void
make_scar()
{
    if (this_object()->query_average_stat() < 10)
	return;
    this_object()->set_scar(this_object()->query_scar() | (1 << random(F_MAX_SCAR)));
}

/*
 * Function name:   num_scar
 * Description:     Get the number of scars a player has
 * Returns:         int holding number of scars
 */
public int
num_scar()
{
    int i, j, n,scar;

    j = 1; n = 0; scar = this_object()->query_scar();

    while (i < F_MAX_SCAR)
    {
    	if (scar & j) n++;
    	j *= 2; i++;
    }
    return n;
}

/*
 * Function name:   desc_scar
 * Description:     Get the composite string holding the scar description
 * Returns:         string holding scar description.
 */
public string
desc_scar()
{
    int i, j, scar;
    string *scar_desc, *my_scars;

    scar_desc = F_SCAR_DESCS;
    scar = this_object()->query_scar();
    j = 1;
    my_scars = 0;
    while(i < F_MAX_SCAR)
    {
	if (scar & j)
	{
	    if (my_scars)
		my_scars = my_scars + ({ scar_desc[i] });
	    else
		my_scars = ({ scar_desc[i] });
	}
	j *= 2;
	i += 1;
    }
    if (!my_scars) return 0;
    if (sizeof(my_scars) == 1)
	return my_scars[0];
    if (sizeof(my_scars) == 2)
	return implode(my_scars, " and ");
    return implode(slice_array(my_scars, 0, sizeof(my_scars) - 2), ", ") +
	" and " + my_scars[sizeof(my_scars) - 1];
}
