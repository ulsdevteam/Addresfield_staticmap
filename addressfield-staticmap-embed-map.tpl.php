<?php if (isset($settings['text_address']) && is_string($settings['text_address'])): ?>
  <div><?php print $settings['text_address']; ?></div>
<?php endif; ?>
  <?php if (isset($settings['directions'])): ?>
  <div><?php print $settings['directions']; ?></div>
<?php endif; ?>
<div id="map_canvas">
    <script type="text/javascript">
        var embedMap = new function(){
           var mapElement = document.createElement("iframe");
           mapElement.src = "https://www.google.com/maps/embed/v1/place?key=<?php print $settings['api_key']?>&q=<?php print $address ?>&zoom=<?php print $settings['zoom']?>";
           mapElement.width = "<?php print $settings['size'] ?>".split("x")[0];
           mapElement.height = "<?php print $settings['size'] ?>".split("x")[1];
           mapElement.frameBorder = "0";
           mapElement.style.border = "0";
           mapElement.allowfullscreen = "true";
           document.getElementById("map_canvas").appendChild(mapElement);
       }
    </script>
</div>


