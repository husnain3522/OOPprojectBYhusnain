-- 1. Create Tables
use restaurant;
CREATE TABLE customers (
    customer_id INT PRIMARY KEY IDENTITY(1,1),
    name NVARCHAR(100) NOT NULL,
    phone NVARCHAR(15) UNIQUE,
    email NVARCHAR(100),
    created_at DATETIME DEFAULT GETDATE()
);

CREATE TABLE staff (
    staff_id INT PRIMARY KEY IDENTITY(1,1),
    name NVARCHAR(100) NOT NULL,
    role NVARCHAR(50) NOT NULL,
    phone NVARCHAR(15) UNIQUE,
    salary DECIMAL(10, 2),
    hired_date DATE DEFAULT GETDATE()
);

CREATE TABLE menu_items (
    item_id INT PRIMARY KEY IDENTITY(1,1),
    name NVARCHAR(100) NOT NULL,
    description NVARCHAR(MAX),
    price DECIMAL(8,2) NOT NULL,
    available_stock INT DEFAULT 0,
    created_at DATETIME DEFAULT GETDATE()
);

CREATE TABLE orders (
    order_id INT PRIMARY KEY IDENTITY(1,1),
    customer_id INT FOREIGN KEY REFERENCES customers(customer_id),
    staff_id INT FOREIGN KEY REFERENCES staff(staff_id),
    order_date DATETIME DEFAULT GETDATE(),
    status NVARCHAR(50) DEFAULT 'Pending',
    total_amount DECIMAL(10,2) DEFAULT 0
);

CREATE TABLE order_items (
    order_item_id INT PRIMARY KEY IDENTITY(1,1),
    order_id INT FOREIGN KEY REFERENCES orders(order_id),
    item_id INT FOREIGN KEY REFERENCES menu_items(item_id),
    quantity INT NOT NULL,
    price_at_order_time DECIMAL(8,2) NOT NULL
);

CREATE TABLE reservations (
    reservation_id INT PRIMARY KEY IDENTITY(1,1),
    customer_id INT FOREIGN KEY REFERENCES customers(customer_id),
    staff_id INT FOREIGN KEY REFERENCES staff(staff_id),
    reservation_date DATETIME NOT NULL,
    guests INT NOT NULL,
    status NVARCHAR(50) DEFAULT 'Booked'
);

CREATE TABLE payments (
    payment_id INT PRIMARY KEY IDENTITY(1,1),
    order_id INT FOREIGN KEY REFERENCES orders(order_id),
    payment_date DATETIME DEFAULT GETDATE(),
    amount DECIMAL(10,2) NOT NULL,
    payment_method NVARCHAR(50) DEFAULT 'Cash'
);

-- 2. Insert Sample Data

INSERT INTO customers (name, phone, email) VALUES
('John Doe', '1234567890', 'john@example.com'),
('Jane Smith', '9876543210', 'jane@example.com'),
('Alice Johnson', '5551234567', 'alice@example.com'),
('Bob Marley', '4443332211', 'bob@example.com'),
('Chris Evans', '7776665555', 'chris@example.com');

INSERT INTO staff (name, role, phone, salary) VALUES
('Mark Brown', 'Manager', '1112223333', 4000.00),
('Emily Davis', 'Waiter', '2223334444', 2500.00),
('Luke Wilson', 'Chef', '3334445555', 3000.00),
('Olivia Stone', 'Waiter', '6665554444', 2600.00),
('Ethan Hunt', 'Cleaner', '9998887777', 2000.00);

INSERT INTO menu_items (name, description, price, available_stock) VALUES
('Margherita Pizza', 'Classic pizza with cheese and tomato sauce', 12.99, 50),
('Cheeseburger', 'Beef burger with cheese, lettuce, and tomato', 9.49, 40),
('Caesar Salad', 'Salad with romaine lettuce, croutons, and parmesan', 7.99, 30),
('Spaghetti Bolognese', 'Pasta with rich meat sauce', 11.49, 35),
('Lemonade', 'Fresh squeezed lemonade', 2.99, 100),
('Grilled Chicken', 'Spicy grilled chicken with herbs', 14.99, 25),
('Chocolate Cake', 'Rich chocolate layered cake', 6.49, 20);

INSERT INTO orders (customer_id, staff_id, status) VALUES
(1, 2, 'Pending'),
(2, 3, 'Pending'),
(3, 2, 'Pending');

INSERT INTO order_items (order_id, item_id, quantity, price_at_order_time) VALUES
(1, 1, 2, 12.99),
(1, 5, 3, 2.99),
(2, 2, 1, 9.49),
(2, 7, 2, 6.49),
(3, 4, 1, 11.49);

INSERT INTO reservations (customer_id, staff_id, reservation_date, guests) VALUES
(1, 2, DATEADD(DAY, 1, GETDATE()), 4),
(2, 3, DATEADD(DAY, 2, GETDATE()), 2),
(5, 2, DATEADD(DAY, 3, GETDATE()), 5);

INSERT INTO payments (order_id, amount, payment_method) VALUES
(1, 44.95, 'Card'),
(2, 22.47, 'Cash');

-- 3. VIEWS

IF OBJECT_ID('view_order_summary', 'V') IS NOT NULL
    DROP VIEW view_order_summary;
GO

-- Step 1: Drop old view if exists
IF OBJECT_ID('view_order_summary', 'V') IS NOT NULL
DROP VIEW view_order_summary;
GO

-- Step 2: Create new view
CREATE VIEW view_order_summary AS
SELECT 
    o.order_id, 
    c.name AS customer_name, 
    s.name AS staff_name, 
    o.order_date, 
    o.total_amount, 
    o.status
FROM orders o
INNER JOIN customers c ON o.customer_id = c.customer_id
INNER JOIN staff s ON o.staff_id = s.staff_id;


IF OBJECT_ID('view_reservation_details', 'V') IS NOT NULL
    DROP VIEW view_reservation_details;
GO

CREATE VIEW view_reservation_details AS
SELECT 
    r.reservation_id, 
    c.name AS customer_name, 
    r.reservation_date, 
    r.guests, 
    r.status
FROM reservations r
INNER JOIN customers c ON r.customer_id = c.customer_id;

IF OBJECT_ID('view_payment_info', 'V') IS NOT NULL
    DROP VIEW view_payment_info;
GO

CREATE VIEW view_payment_info AS
SELECT 
    p.payment_id, 
    c.name AS customer_name, 
    p.amount, 
    p.payment_method
FROM payments p
INNER JOIN orders o ON p.order_id = o.order_id
INNER JOIN customers c ON o.customer_id = c.customer_id;

IF OBJECT_ID('view_available_menu', 'V') IS NOT NULL
    DROP VIEW view_available_menu;
GO

CREATE VIEW view_available_menu AS
SELECT 
    name, 
    price, 
    available_stock
FROM menu_items
WHERE available_stock > 0;

IF OBJECT_ID('view_staff_roles', 'V') IS NOT NULL
    DROP VIEW view_staff_roles;
GO

CREATE VIEW view_staff_roles AS
SELECT 
    role, 
    COUNT(*) AS total_staff
FROM staff
GROUP BY role;

-- 4. TRIGGERS

-- Trigger 1: Decrease stock after new order item
CREATE TRIGGER trg_decrease_stock
ON order_items
AFTER INSERT
AS
BEGIN
    UPDATE menu_items
    SET available_stock = available_stock - inserted.quantity
    FROM menu_items
    INNER JOIN inserted ON menu_items.item_id = inserted.item_id;
END;

-- Trigger 2: Update order total after inserting order item
CREATE TRIGGER trg_update_order_total
ON order_items
AFTER INSERT
AS
BEGIN
    UPDATE orders
    SET total_amount = total_amount + (inserted.price_at_order_time * inserted.quantity)
    FROM orders
    INNER JOIN inserted ON orders.order_id = inserted.order_id;
END;

-- Trigger 3: Set reservation status to completed automatically
CREATE TRIGGER trg_auto_complete_reservation
ON reservations
AFTER INSERT
AS
BEGIN
    UPDATE reservations
    SET status = 'Completed'
    WHERE reservation_date < GETDATE();
END;

-- Trigger 4: Prevent negative stock
CREATE TRIGGER trg_check_stock
ON order_items
AFTER INSERT
AS
BEGIN
    IF EXISTS (
        SELECT 1
        FROM menu_items m
        INNER JOIN inserted i ON m.item_id = i.item_id
        WHERE m.available_stock < 0
    )
    BEGIN
        RAISERROR('Stock cannot go negative!', 16, 1);
        ROLLBACK TRANSACTION;
    END
END;

-- Trigger 5: Default payment method
CREATE TRIGGER trg_default_payment
ON payments
INSTEAD OF INSERT
AS
BEGIN
    INSERT INTO payments (order_id, payment_date, amount, payment_method)
    SELECT
        order_id,
        GETDATE(),
        amount,
        ISNULL(payment_method, 'Cash')
    FROM inserted;
END;

-- 5. SUBQUERIES

-- Customers with more than 1 order
SELECT name FROM customers
WHERE customer_id IN (SELECT customer_id FROM orders GROUP BY customer_id HAVING COUNT(*) > 1);

-- Most expensive item
SELECT name FROM menu_items
WHERE price = (SELECT MAX(price) FROM menu_items);

-- Staff with salary greater than average
SELECT name FROM staff
WHERE salary > (SELECT AVG(salary) FROM staff);

-- Orders with total above average
SELECT order_id FROM orders
WHERE total_amount > (SELECT AVG(total_amount) FROM orders);

-- Reservations with more guests than average
SELECT reservation_id FROM reservations
WHERE guests > (SELECT AVG(guests) FROM reservations);

-- 6. NESTED QUERIES

-- Customer and their most recent order date
SELECT name, (SELECT MAX(order_date) FROM orders WHERE customer_id = c.customer_id) AS last_order
FROM customers c;

-- Staff and highest order amount handled
SELECT name, (SELECT MAX(total_amount) FROM orders WHERE staff_id = s.staff_id) AS max_order
FROM staff s;

-- Top 3 expensive menu items
SELECT * FROM (
    SELECT name, price FROM menu_items ORDER BY price DESC
) AS top3
WHERE price >= (
    SELECT MIN(price) FROM (
        SELECT TOP 3 price FROM menu_items ORDER BY price DESC
    ) AS temp
);

-- Customers with pending orders
SELECT * FROM customers
WHERE customer_id IN (
    SELECT customer_id FROM orders WHERE status = 'Pending'
);

-- Low stock menu items
SELECT * FROM (
    SELECT name, available_stock FROM menu_items WHERE available_stock < 10
) AS low_stock;
