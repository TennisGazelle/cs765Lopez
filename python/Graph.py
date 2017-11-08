from graph_tool.all import *

class Graph:
    ug = Graph(directed = False)
    verticies = []
    edges = []
    props = {}

    def __init__(self):
        self.props["vert_name"] = self.ug.new_vertex_property("string")
        self.props["vert_value"] = self.ug.new_vertex_property("float")
        self.props["edge_value"] = self.ug.new_edge_property("int")

        self.ug.vertex_properties["vert_name"] = self.props["vert_name"]
        self.ug.vertex_properties["vert_value"] = self.props["vert_value"]
        self.ug.edge_properties["edge_value"] = self.props["edge_value"]

    def newVertex(self, name, value, createEdge = False):
        vert = self.ug.add_vertex()
        self.props["vert_name"][vert] = name
        self.props["vert_value"][vert] = value

        #add an edge against everything else in the thing
        if createEdge:
            for v in self.verticies:
                connectionValue = self.props["vert_value"][v] + self.props["vert_value"][vert]
                e = self.ug.add_edge(vert, v)
                self.props["edge_value"][e] = connectionValue
                self.edges += [e]

        self.verticies += [vert]
    
    def draw(self):
        for v in self.verticies:
            print ("vertex:", self.props["vert_name"][v])

        graph_draw(
            self.ug,
            vertex_text = self.ug.vertex_properties["vert_name"],
            edge_text = self.ug.edge_properties["edge_value"],
            vertex_font_size = 18,
            edge_font_size = 18,
            vertex_size = self.ug.vertex_properties["vert_value"],
            edge_pen_width = self.ug.edge_properties["edge_value"],
            output_size = (600, 600),
            output = "graph.png"
            )

if __name__ == '__main__':
    gra = Graph()
    gra.newVertex("AAPL", 2)
    gra.newVertex("COST", 2)
    gra.newVertex("SOME NODE", 10)
    gra.newVertex("THIRD NODE", 40)
    gra.newVertex("HEMAN", 20)
    gra.draw()