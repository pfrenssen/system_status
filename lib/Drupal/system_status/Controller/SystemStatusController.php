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
 * Returns responses for Pants routes.
 */
class SystemStatusController extends ControllerBase {

  /**
   * Changes pants status and returns the display of the new status.
   *
   * @param \Drupal\user\UserInterface $user
   *   A user object.
   */
  function load() {

  	$all_modules = _system_rebuild_module_data();
    $config = $this->config('system_status.settings');
    $system_modules = (array) \Drupal::config('system.module')->get('enabled');
    // Needless initialisation, but hey.
    $res = array(
      "core" => array(),
      "contrib" => array(),
      "custom" => array(),
    );

    foreach ($all_modules as $module => $module_info) {
      if (in_array($module_info->name , array_keys($system_modules))) {
	      $filename = $module_info->filename;
	      // Match for custom modules.
	      if ($config->get('system_status_do_match_custom')) {
	        $regex = $config->get('system_status_preg_match_custom');
	        if (preg_match($regex, $filename)) {
	          // if this is part of a project, only set the project.
	          if(isset($module_info->info['project'])) {
	            $res['custom'][$module_info->info['project']] = array("version" => $module_info->info['version']);
	          }
	          else {
	            $res['custom'][$module] = array("version" => $module_info->info['version']);
	          }
	        }
	      }
	      else {
	        $res['custom'] = "disabled";
	      }
	
	      // Match for contrib modules.
	      if ($config->get('system_status_do_match_contrib')) {
	        if ($config->get('system_status_match_contrib_mode') == 0) {
	          $regex = '{^modules\/*}';
	        }
	        elseif ($config->get('system_status_match_contrib_mode') == 1) {
	          $regex = '{^modules\/contrib\/*}';
	        }
	        else {
	          $regex = $config->get('system_status_preg_match_contrib');
	        }
	        if (preg_match($regex, $filename)) {
	          // if this is part of a project, only set the project.
	          if(isset($module_info->info['project'])) {
	            $res['contrib'][$module_info->info['project']] = array("version" => $module_info->info['version']);
	          }
	          else {
	            $res['contrib'][$module] = array("version" => $module_info->info['version']);
	          }
	        }
	      }
	      else {
	        $res['contrib'] = "disabled";
	      }
	
	      // Core modules.
	      if ($config->get('system_status_do_match_core')) {
	        if (strtolower($module_info->info['package']) == "core") {
	          // if this is part of a project, only set the project.
	          if(isset($module_info->info['project'])) {
	            $res['core'][$module_info->info['project']] = array("version" => $module_info->info['version']);
	          }
	          else {
	            $res['core'][$module] = array("version" => $module_info->info['version']);
	          }
	        }
	      }
	      else {
	        $res['core'] = "disabled";
	      }
      }
    }

    if (($config->get('system_status_need_encryption') == 1 || $config->get('system_status_service_allow_drupalstatus') == 1) && extension_loaded('mcrypt')) {
      $res = SystemStatusEncryption::encrypt(json_encode(array("system_status" => $res)));
      return new JsonResponse(array("system_status" => "encrypted", "data" => $res, "drupal_version" => "8"));
    }
    else {
      return new JsonResponse(array("system_status" => $res, "drupal_version" => "8"));
    }
  }

}
