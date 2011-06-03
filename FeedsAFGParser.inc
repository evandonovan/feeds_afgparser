<?php
/**
* A simple parser that extends FeedsSimplePieParser by adding support for AllForGood's Footprint XML tags.
*/
class FeedsAFGParser extends FeedsSimplePieParser {
  /**
   * Define the extra mapping sources from the AFG feed.
   */
  public function getMappingSources() {
    return parent::getMappingSources() + array(
      /* Custom field source for enforcing uniqueness. */
      // TODO: determine why this isn't working as GUID.
      'stripped_guid' => array(
        'name' => t('Stripped GUID'),
        'description' => t('The GUID stripped of the fp:id which is appended after a hash character (#). This should be used as the GUID. It should be equivalent to fp:detailurl, but that doesn\'t show up in the AFG feed output.'),
      ),
      /* Fields that are always present on an AFG feed. */
      'fp_id' => array(
        'name' => t('AFG Hash (fp:id)'),
        'description' => t('Hashed ID of the opportunity in AFG feed output. Supposedly changes each day.'),
      ),
      'fp_groupid' => array(
        'name' => t('ID of Merged Opps (fp:groupid)'),
        'description' => t('An ID for a deduped set of results.'),
      ),
      'fp_provider' => array(
        'name' => t('Opportunity Source (fp:provider)'),
        'description' => t('Provider of the opportunity. It is a "machine name", so is always lowercase and will not necessarily have spaces.'),
      ),
      'fp_startDate' => array(
        'name' => t('Opportunity Start Date (fp:startDate)'),
        'description' => t('The start date for a volunteer opportunity.'),
      ),
      'fp_endDate' => array(
        'name' => t('Opportunity End Date (fp:endDate)'),
        'description' => t('The end date for a volunteer opportunity.'),
      ),
      'fp_base_url' => array(
        'name' => t('AFG Hash (fp:base_url)'),
        'description' => t('Same as fp:id.'),
      ),
      'fp_xml_url' => array(
        'name' => t('Opportunity URL with Hash (fp:xml_url)'),
        'description' => t('Full URL to opportunity, including hash. (Same as GUID of opportunity.)'),
      ),
      'fp_url_short' => array(
        'name' => t('Opportunity URL Domain Name (fp:url_short)'),
        'description' => t('The domain name of the site where the original opportunity listing is found.'),
      ),
      'fp_latlong' => array(
        'name' => t('AFG-style Latitude/Longitude (fp:latlong)'),
        'description' => t('Latitude, Longitude to seven digits of precision. Needs custom parsing to be mapped.'),
      ),
      'fp_location_name' => array(
        'name' => t('Opportunity City, State Zip (fp:location_name)'),
        'description' => t('Opportunity location, with city, state, and zip all in one field.'),
      ),
      'fp_interest_count' => array(
        'name' => t('Clickthrus? (fp:interest_count)'),
        'description' => t('Unsure - possibly number of clickthrus.'),
      ),
      'fp_impressions' => array(
        'name' => t('Number of Pageviews? (fp:impressions)'),
        'description' => t('Unsure - possibly number of pageviews, possibly related to an ad campaign.'),
      ),
      'fp_quality_score' => array(
        'name' => t('AFG Opportunity Rating (fp:quality_score)'),
        'description' => t('Internal rating from 0 to 10 of quality of opportunity.'),
      ),
      'fp_virtual' => array(
        'name' => t('Virtual Opportunity Status (fp:virtual)'),
        'description' => t('Whether opportunity is virtual - True or False.'),
      ),
      'fp_sponsoringOrganizationName' => array(
        'name' => t('Sponsoring Organization Name (fp:sponsoringOrganizationName)'),
        'description' => t('Name of organization offering this opportunity.'),
      ),
      'fp_openEnded' => array(
        'name' => t('Open-Ended Opportunity Status (fp:openEnded)'),
        'description' => t('Whether opportunity is open-ended (no specific start or end date).'),
      ),
      'fp_startTime' => array(
        'name' => t('Opportunity Start Time (fp:startTime)'),
        'description' => t('Opportunity start time.'),
      ),
      'fp_endTime' => array(
        'name' => t('Opportunity End Time (fp:endTime)'),
        'description' => t('Opportunity end time.'),
      ),
      /* Fields that are sometimes present on an AFG feed. */
      'fp_skills' => array(
        'name' => t('Opportunity Skills (fp:skills)'),
        'description' => t('Skills needed for this opportunity. (Many providers use this as a detailed description.)'),
      ),
      'fp_contactEmail' => array(
        'name' => t('Email Address for Primary Contact (fp:contactEmail)'),
        'description' => t('The email address for the primary contact for the opportunity.'),
      ),
      'fp_contactPhone' => array(
        'name' => t('Phone Number for Primary Contact (fp:contactPhone)'),
        'description' => t('The phone number for the primary contact for the opportunity.'),
      ),
      /* Feeds that are never (so far) present on an AFG feed. */
      'fp_categories' => array(
        'name' => t('Opportunity Categories (fp:categories)'),
        'description' => t('The categories with which the opportunity is tagged. (Providers won\'t usually offer this.)'),
      ),
      'fp_s' => array(
        'name' => t('fp:s'),
        'description' => t('Unsure.'),
      ),
      'fp_m' => array(
        'name' => t('fp:m'),
        'description' => t('Unsure.'),
      ),
      'fp_addr1' => array(
        'name' => t('First Line of Address? (fp:addr1)'),
        'description' => t('First line of address?'),
      ),
      'fp_addrname' => array(
        'name' => t('Address Name? (fp:addrname)'),
        'description' => t('Address Name?'),
      ),
      'fp_contactNoneNeeded' => array(
        'name' => t('fp:contactNoneNeeded'),
        'description' => t('Unsure.'),
      ),
      'fp_contactName' => array(
        'name' => t('Name of Primary Contact? (fp:contactName)'),
        'description' => t('Name of Primary Contact?'),
      ),
      'fp_detailUrl' => array(
        'name' => t('Link to Original Opportunity? (fp:detailUrl)'),
        'description' => t('Link to Original Opportunity?'),
      ),
      'fp_audienceAll' => array(
        'name' => t('fp:audienceAll'),
        'description' => t('Unsure.'),
      ),
      'fp_audienceAge' => array(
        'name' => t('Acceptable Ages? (fp:audienceAge)'),
        'description' => t('What ages of volunteer the opportunity is suited for?'),
      ),
      'fp_minAge' => array(
        'name' => t('Minimum Age? (fp:minAge)'),
        'description' => t('Minimum age for volunteers?'),
      ),
      'fp_audienceSexRestricted' => array(
        'name' => t('Volunteers Only of a Particular Gender? (fp:audienceSexRestricted)'),
        'description' => t('Whether volunteers can only be of a particular gender?'),
      ),
      'fp_street1' => array(
        'name' => t('Street Address Line 1? (fp:street1)'),
        'description' => t('Street Address Line 1?'),
      ),
      'fp_street2' => array(
        'name' => t('Street Address Line 2? (fp:street2)'),
        'description' => t('Street Address Line 2?'),
      ),
      'fp_city' => array(
        'name' => t('City? (fp:city)'),
        'description' => t('City?'),
      ),
      'fp_region' => array(
        'name' => t('Region/State? (fp:region)'),
        'description' => t('Region/State?'),
      ),
      'fp_postalCode' => array(
        'name' => t('Postal Code/Zipcode? (fp:postalCode)'),
        'description' => t('Postal Code/Zipcode?'),
      ),
      'fp_country' => array(
        'name' => t('Country? (fp:country)'),
        'description' => t('Country?'),
      ),
    );
  }

  /**
   * Parse the extra mapping sources from the AFG feed.
   */
  protected function parseExtensions(&$item, $simplepie_item) {
    // define the AllForGood namespace (needed for SimplePie's get_item_tags() method)
    $afg_namespace = 'http://www.allforgood.org/';
    // define the tags from the AFG feed
    // TODO: do a custom mapping for latlong that splits it into two (possibly others need custom also)
    $fp_tags = array('id', 'groupid', 'provider', 'startDate', 'endDate', 'base_url', 'xml_url',
                      'url_short', 'latlong', 'location_name', 'interest_count', 'impressions', 
                      'quality_score', 'virtual', 'sponsoringOrganizationName', 'openEnded', 'startTime',
                      'endTime', 'skills', 'contactEmail', 'contactPhone', 'categories', 's', 'm', 'v',
                      'addr1', 'addrname1', 'contactNoneNeeded', 'contactName', 'detailUrl',
                      'audienceAll', 'audienceAge', 'minAge', 'audienceSexRestricted', 'street1',
                      'street2', 'city', 'region', 'postalCode', 'country');
    // set the value for "stripped_guid"
    if ($value = $simplepie_item->get_id()) {
      // split the GUID on the '#' and set the stripped_guid to be just the part before it
      $guid_pieces = explode('#', $value);
      $item['stripped_guid'] = $guid_pieces[0];
    }
    // set the values for the AFG tags
    foreach($fp_tags as $tagname) {
      if($value = $simplepie_item->get_item_tags($afg_namespace, $tagname)) {
        $item['fp_' . $tagname] = $value[0]['data'];
      }
    }
  }
}