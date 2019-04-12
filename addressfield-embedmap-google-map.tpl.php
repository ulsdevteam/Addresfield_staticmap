<?php $size = explode('x', $settings['size']); ?>

<?php if (isset($settings['text_address']) && is_string($settings['text_address'])): ?>
  <div><?php print $settings['text_address']; ?></div>
<?php endif; ?>

<div id="map_canvas<?php if(isset($settings['id'])) print '-'.$settings['id']; ?>" style="width: <?php print $size[0]; ?>px; height: <?php print $size[1]; ?>px;">
  <noscript><?php print $image; ?></noscript>
</div>

<script type="text/javascript">
var staticMapGoogleMap<?php if(isset($settings['id'])) print '_'.$settings['id']; ?> = new function() {
  var address = '<?php print $address; ?>';

  var myOptions = {
  <?php if ($settings['zoom'] !== 'auto'): ?>zoom: <?php print $settings['zoom']; ?>,<?php endif ?>
    mapTypeId: google.maps.MapTypeId.<?php print strtoupper($settings['maptype']); ?>,
    scale: <?php print $settings['scale']; ?>,
    scrollwheel: <?php print $settings['scroll_lock'] ? 'false' : 'true'; ?>,
    <?php if ($settings['scroll_lock']) print 'gestureHandling: "none",' ?>
    zoomControl: <?php print $settings['scroll_lock'] ? 'false' : 'true'; ?>,
  }
  var map = new google.maps.Map(document.getElementById('map_canvas<?php if(isset($settings['id'])) print '-'.$settings['id']; ?>'), myOptions);

  <?php if (isset($settings['info_window'])): ?>
  // info window
  var content = document.createElement('div');
  content.className = 'info-window';
  content.innerHTML = '<?php print $settings['text_address']; ?>';

  var infowindow = new google.maps.InfoWindow({
  content: content
  });
  <?php endif; ?>

  <?php foreach ($kml_paths as $kml_path): ?>
  var ctaLayer = new google.maps.KmlLayer('<?php print $kml_path; ?>');
  ctaLayer.setMap(map);
  <?php endforeach; ?>

  var geocoder = new google.maps.Geocoder();

  geocoder.geocode({'address': address}, function(results, status) {
    if (status == google.maps.GeocoderStatus.OK) {
      map.setCenter(results[0].geometry.location);
      var marker = new google.maps.Marker({
      map: map,
        position: results[0].geometry.location
      });
      <?php if (isset($settings['info_window'])): ?>
      // info window
      google.maps.event.addListener(marker, 'click', function() {
        infowindow.open(map,marker);
      });
      <?php endif; ?>
    }
  });
}
</script>

/*<?php if (isset($settings['link'])): ?>
//
//<div id="map_canvas<?php if(isset($settings['id'])) print '-'.$settings['id']; ?>" style="width: <?php print $size[0]; ?>px; height: <?php print $size[1]; ?>px;">
//  <noscript><?php print '<p> helloooo</p>'; ?></noscript>
//  <p>Test injecting html </p>
//<script type="text/javascript">
//    var embedMap = new function(){
//        var address = "700+Thomas+Boulevard,Pittsburgh,PA";
//        var mapElement = document.createElement("iframe");
//        var api_key = "AIzaSyCn8AnqdP2c_1eIqeHe3ORPIekh6neqk2I";
 //       mapElement.src = "https://www.google.com/maps/embed/v1/place?key="+api_key+" &q="+address+" &zoom=15";
//        mapElement.width = "400";
 //       mapElement.height = "400";
 //       mapElement.frameBorder = "0";
 //       mapElement.style.border = "0";
 //       mapElement.allowfullscreen = "true";
//        document.getElementById("map_canvas").appendChild(mapElement);
//    }
//</script>
//<?php endif; ?>
//<?php if (isset($settings['link'])): ?>
 // </div>
//<?php endif; ?>
*/
/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

