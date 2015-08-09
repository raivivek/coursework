1.

# Final
mysql> SELECT product.pid, product.name
        FROM product, inventory
        WHERE product.pid = inventory.pid AND inventory.stock < 5;

2.

# Final
mysql> SELECT DISTINCT supplier.sid, supplier.name FROM supplies JOIN manufactures USING(pid) JOIN supplier USING(sid) JOIN manufacturer USING(mid) WHERE manufacture.name = 'manufacturer_2';

3. 

# Final
mysql> SELECT product.pid, name, inventory.stock FROM product, inventory WHERE product.pid = inventory.pid ORDER BY stock DESC;

4.

# Final
mysql> SELECT pid, name, COUNT(*) as `num` FROM product JOIN supplies USING(pid) GROUP BY pid HAVING num = 1;

5.

# Final
SELECT pid, product.name FROM product JOIN inventory USING(pid) WHERE stock = (SELECT MIN(stock) FROM inventory);

6.

# Final
SELECT sid, name, COUNT(*) as `product_supplied` FROM supplier JOIN supplies USING (sid) GROUP BY sid;

7.

# Final
SELECT manufactures.mid, manufacturer.name, AVG(min_age) FROM manufactures JOIN product USING(pid) JOIN manufacturer USING(mid) GROUP BY mid ORDER BY min_age DESC LIMIT 1;

8.

# Final
SELECT mid, name, COUNT(*) AS `products_produced` FROM manufacturer JOIN manufactures USING(mid) GROUP BY mid ORDER BY `products_produced` DESC LIMIT 1;
