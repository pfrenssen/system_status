<?php

/**
 * @file
 * Contains \Drupal\pants\Controller\SystemStatusController.
 */

namespace Drupal\system_status\Controller;

use Drupal\Core\Controller\ControllerBase;
use Drupal\user\UserInterface;
use Drupal\system_status\Controller\SystemStatusEncryption;
use Symfony\Component\HttpFoundation\JsonResponse;


/**
 * Returns responses for Sensei's Pants routes.
 */
class SystemStatusController extends ControllerBase {

  /**
   * Changes Sensei's pants and returns the display of the new status.
   */
  function load() {

    // Needless initialisation, but hey.
    $res = array(
      "core" => array(),
      "contrib" => array(),
      "custom" => array(),
    );

    $drupal_modules = \Drupal::moduleHandler()->getModuleDirectories();
    foreach($drupal_modules as $modulename => $folder) {
	$module = \Drupal::service('info_parser')->parse($folder . "/" . $modulename . ".info.yml");

	// do our best to guess the correct drupal version
	if($modulename == "system" && $module['package'] == "Core") 
		$res['core']['drupal'] = array("version" => $module['version']); 

	
	// only do modules
	if($module['type'] != "module")
	   continue;

	// Skip Core and Field types 
	if($module['package'] == "Core" || $module['package'] == "Field types")
	   continue;

	// TODO:
	// if(!isset($module['version']))
	// we can be 90% sure it's not contrib, so we can put it in custom
	// hard to test as system_status is not released yet so no version
	// let's put all the rest in 'contrib' for now

	if(isset($module['project'])) {
		$res['contrib'][$module['project']] = array("version" => $module['version']);
	} else {
		$res['contrib'][$modulename] = array("version" => $module['version']);
	}
    }
  
    $config = \Drupal::config('system_status.settings');
    if (($config->get('system_status_need_encryption') == 1 || $config->get('system_status_service_allow_drupalstatus') == 1) && extension_loaded('mcrypt')) {
      $res = SystemStatusEncryption::encrypt(json_encode(array("system_status" => $res)));
      return new JsonResponse(array("system_status" => "encrypted", "data" => $res, "drupal_version" => "8"));
    }
    else {
      return new JsonResponse(array("system_status" => $res, "drupal_version" => "8"));
    }
  }

}
