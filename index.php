<?php

$logFile = "log.txt";
$hitCounter = "counter.txt";

$r = array();

$r['datetime'] = date('Y-m-d H:i:s');
$r['ip'] = $_SERVER['REMOTE_ADDR'];

$r['randseed'] = $_REQUEST['randseed'];
$r['hostname'] = $_REQUEST['hostname'];
$r['username'] = $_REQUEST['username'];
$r['macaddrs'] = $_REQUEST['macaddrs'];
$r['version']  = $_REQUEST['version'];
$r['edition']  = $_REQUEST['edition'];

$hit = file_exists($hitCounter)? file_get_contents($hitCounter) : 0;
$hit++;
file_put_contents($hitCounter, $hit);
$r['hit'] = $hit;

if(isset($_REQUEST['debug']))
{
	echo "<pre>";
	print_r($r);
	echo "</pre>";
}

$log = "";
$log .= "Hit      : " . $r['hit'] . "\n";
$log .= "Time     : " . $r['datetime'] . "\n";
$log .= "IP       : " . $r['ip'] . "\n";
$log .= "randseed : " . $r['randseed'] . "\n";
$log .= "hostname : " . $r['hostname'] . "\n";
$log .= "username : " . $r['username'] . "\n";
$log .= "macaddrs : " . $r['macaddrs'] . "\n";
$log .= "version  : " . $r['version'] . "\n";
$log .= "edition  : " . $r['edition'] . "\n";
$log .= "------------------------------\n";

file_put_contents($logFile, $log, FILE_APPEND);

// Latest Version
echo "2.0.0\n";

// Message
//echo "Happy New Year !\n";
