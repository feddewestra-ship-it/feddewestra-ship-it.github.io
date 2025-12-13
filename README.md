# nexo maps
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8">
    <title>OpenStreetMap met Leaflet.js</title>
    <link rel="stylesheet" href="https://unpkg.com/leaflet/dist/leaflet.css" />
    <style>
        #map { height: 500px; }
    </style>
</head>
<body>
    <h6>PRE-ALPHA! V0.2</h6>
    <div id="map"></div>

    <script src="https://unpkg.com/leaflet/dist/leaflet.js"></script>
    <script>
        // Maak een kaart met Leaflet
        var map = L.map('map').setView([52.3702, 4.8952], 13); // Amsterdam

        // Voeg een OpenStreetMap-tegel laag toe
        L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
            maxZoom: 19,
        }).addTo(map);

        // Voeg een marker toe op de kaart
        L.marker([52.3702, 4.8952]).addTo(map)
            .bindPopup('Amsterdam!')
            .openPopup();
    </script>
</body>
</html>
