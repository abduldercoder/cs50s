-- The average energy of songs thar are by Drake
SELECT AVG(energy) FROM songs JOIN artists ON songs.artist_id = artists.id WHERE artists.name = 'DRAKE';
