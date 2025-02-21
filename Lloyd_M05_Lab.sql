-- Create Tables and Insert Records
CREATE TABLE CUSTOMER (
    cust_id INT PRIMARY KEY,
    first_name VARCHAR(50),
    last_name VARCHAR(50),
    email VARCHAR(100)
);
-- Create AGENT table
CREATE TABLE AGENT (
    agent_id INT PRIMARY KEY,
    first_name VARCHAR(50),
    last_name VARCHAR(50),
    department VARCHAR(100)
);
--Create SERVICE table
CREATE TABLE SERVICE (
    service_id INT PRIMARY KEY,
    service_name VARCHAR(100)
);

-- Create SUBSCRIPTION table
CREATE TABLE SUBSCRIPTION (
    subscription_id INT PRIMARY KEY,
    service_id INT,
    cust_id INT,
    agent_id INT,
    start_date DATE,
    renew_date DATE,
    FOREIGN KEY (service_id) REFERENCES SERVICE(service_id),
    FOREIGN KEY (cust_id) REFERENCES CUSTOMER(cust_id),
    FOREIGN KEY (agent_id) REFERENCES AGENT(agent_id)
);
CREATE Table Transaction (
    transaction_id INT PRIMARY KEY,
    subscription_id INT,
    cust_id INT,
    transaction_date DATE,
    amount DECIMAL(10,2),
    FOREIGN KEY (subscription_id) REFERENCES SUBSCRIPTION(subscription_id),
    FOREIGN KEY (cust_id) REFERENCES CUSTOMER(cust_id)
);

-- Insert records into the SERVICE table
INSERT INTO SERVICE (service_id, service_name) VALUES
(101, 'Web Hosting'),
(201, 'SEO Optimization'),
(301, 'Cloud Storage'),
(401, 'Network Services'),
(501, 'Security Services'),
(601, 'Storage Solutions');

-- Insert records into the CUSTOMER table
INSERT INTO CUSTOMER (cust_id, first_name, last_name, email) VALUES
(1001, 'Danielle', 'Lloyd', 'DLloyd616@outlook.com'),
(1002, 'Dennis', 'Lloyd', 'denlloyd@example.com'),
(1003, 'Jackie', 'Robinson', 'drobin@example.com'),
(1004, 'Jill', 'Smith', 'jsmith@example.com'),
(1005, 'John', 'Doe', 'jdoe@example.com');

-- Insert records into the AGENT table
INSERT INTO AGENT (agent_id, first_name, last_name, department) VALUES
('AS1001', 'Alex', 'Smith', 'Sales'),
('JD1002', 'Joe', 'Dougly', 'Sales'),
('SA1003', 'Steph', 'Andrews', 'Sales'),
('AH1004', 'Alexis', 'Hazel', 'IT'),
('PD1005', 'Pete', 'Davidson', 'IT');

INSERT INTO CUSTOMER (cust_id, first_name, last_name, email)
VALUES (1589, 'Alice', 'Johnson', 'alice.johnson@example.com');