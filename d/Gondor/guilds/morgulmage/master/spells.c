/*
 * Function name: query_sulambar_charges
 * Description  : See how much charges the mage has left for Sulambar
 *              : This function also makes sure the value is recharged.
 * Arguments    : mage - the mage to check for
 * Returns      : a number
 */
public int query_sulambar_charges(object mage)
{
    string magename = get_mage_real_name(mage);
    initialize_member(magename);
	int		regenerated_charges;

	// We don't work on non mages
	if(!IS_MEMBER(mage)) return 0;

	// Check for member, if they dont exist yet, let them start with the max
	// number of charges.
	if(member_array("sulambar_charges", m_indices(member_information[magename])) == -1)
		member_information[magename]["sulambar_charges"] = 
            ({ mage->query_age(), MAX_SULAMBAR_CHARGES });

	// See how many charges have regenerated
	regenerated_charges = (mage->query_age() - member_information[magename]["sulambar_charges"][0]) / 
		SULAMBAR_REGEN_TIME;
	if(regenerated_charges > 0) 
	{
		// Reset the time to the new value
		member_information[magename]["sulambar_charges"][0] += (regenerated_charges * 
			SULAMBAR_REGEN_TIME);

		// Make sure we never recharge over the max charges
		if((member_information[magename]["sulambar_charges"][1] + regenerated_charges) > 
			MAX_SULAMBAR_CHARGES)
		{
			regenerated_charges = MAX_SULAMBAR_CHARGES - 
				member_information[magename]["sulambar_charges"][1];
		}

		// Add the charges
		member_information[magename]["sulambar_charges"][1] += regenerated_charges;

		// Store the data
		save_data();
	}

	return member_information[magename]["sulambar_charges"][1];
}

/*
 * Function name: decrease_sulambar_charge
 * Description  : Remove one of the mage's sulambar charges
 * Arguments    : mage - the object of the mage casting sulambar
 */
void decrease_sulambar_charge(object mage)
{
    string magename = get_mage_real_name(mage);
    initialize_member(magename);

	// We don't work on non mages
	if(!IS_MEMBER(mage)) return 0;

	// Check for member, if they dont exist yet, let them start with the max
	// number of charges.
	if(member_array("sulambar_charges", m_indices(member_information[magename])) == -1)
		member_information[magename]["sulambar_charges"] = 
            ({ mage->query_age(), MAX_SULAMBAR_CHARGES });

	// Substract the charge
	member_information[magename]["sulambar_charges"][1]--;

	// Store the data
	save_data();
}
